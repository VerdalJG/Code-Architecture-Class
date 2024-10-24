#include "RenderManager.h"
#include "Globals.h"
#include "TimerManager.h"
#include "Sprite.h"
#include "Entity.h"
#include "Background.h"
#include "Widget.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include "CursorWidget.h"
#include "WorldManager.h"
#include "World.h"


#include <include/rapidjson/rapidjson.h>
#include <include/rapidjson/document.h>
#include <include/rapidjson/writer.h>
#include <include/rapidjson/filereadstream.h>
#include <include/rapidjson/stringbuffer.h>
#include <iostream>
#include <cctype>
using namespace rapidjson;

RenderEngine& RenderEngine::GetInstance()
{
	static RenderEngine instance;
	return instance;
}

void RenderEngine::Initialize(TimeManager* _Timer)
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen."data/circle-bkg-128.png", true
	
	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.

	timer = _Timer;
}

void RenderEngine::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.
	
	RenderBackground(WorldManager::GetInstance().GetCurrentWorld()->GetBackground());
	RenderSprites();
	RenderUI();
	//DisplayTimerValues();
	//RenderJSONData();

	// Exchanges the front and back buffers
	SYS_Show();
}

void RenderEngine::DisplayTimerValues()
{
	// Buffers for strings below
	char fpsBuffer[50];
	char realTimeBuffer[50];
	char logicTimeBuffer[50];

	// Concatenate string with numbers
	snprintf(fpsBuffer, 50, "FPS: %f", timer->GetFPS());
	snprintf(realTimeBuffer, 50, "RT: %f", timer->GetTime());
	snprintf(logicTimeBuffer, 50, "LT: %f", timer->GetLogicTime());

	// Text
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 50), fpsBuffer);
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 70), realTimeBuffer);
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 90), logicTimeBuffer);
}

void RenderEngine::RenderJSONData()
{
	//Print JSON content
	FILE* file = fopen("data/Test.json", "rb");
	char buffer[65536];
	FileReadStream stream(file, buffer, sizeof(buffer));
	Document document;
	document.ParseStream(stream);
	fclose(file);

	int line = 8;
	for (Value::ConstMemberIterator iterator = document.MemberBegin(); iterator != document.MemberEnd(); ++iterator)
	{
		char documentString[50] = { 0 };

		// Convert keys/names of JSON members to uppercase
		std::string str = iterator->name.GetString();
		for (char& c : str) 
		{
			c = std::toupper(c);
		}

		// Get the value and value type
		Type valueType = iterator->value.GetType();
		const Value& value = document[iterator->name];

		// Handle different value types
		std::string valueString;
		switch (valueType)
		{
			case Type::kStringType:
				valueString = iterator->value.GetString();
				for (char& c : valueString) 
				{
					c = std::toupper(c);
				}
				snprintf(documentString, 50, "%s : %s", str.c_str(), valueString.c_str());
				break;
			case Type::kTrueType:
				valueString = "TRUE";
				break;
			case Type::kFalseType:
				valueString = "FALSE";
				break;
			case Type::kNullType:
				valueString = "NULL";
				break;
			case Type::kNumberType:
				if (iterator->value.IsInt()) 
				{ 
					valueString = std::to_string(iterator->value.GetInt()); 
				}
				else if (iterator->value.IsFloat()) 
				{ 
					valueString = std::to_string(iterator->value.GetFloat()); 
				}
				else if (iterator->value.IsDouble()) 
				{
					valueString = std::to_string(iterator->value.GetDouble());
				}
				break;
			case Type::kArrayType:
				for (unsigned int i = 0; i < value.Size(); i++)
				{
					valueString += std::to_string(value[i].GetInt());
				}
				break;
			default:
				break;
		}

		// Print strings on the right of the screen, use 'line' to perform this for every string so they don't overlap
		snprintf(documentString, 50, "%s : %s", str.c_str(), valueString.c_str());
		FONT_DrawString(vec2(SCR_WIDTH - 256, SCR_HEIGHT - 16 * line), documentString);
		line++;
	}
}

void RenderEngine::Terminate()
{
	// Unload font.
	UnloadAllSprites();
	FONT_End();
	delete(background);
}

void RenderEngine::RenderBackground(Background* background)
{
	if (background)
	{
		if (background->IsTiled())
		{
			Sprite* backgroundSprite = background->GetTexture();
			// Render tiled image
			int sizeX = backgroundSprite->GetSize().x;
			int sizeY = backgroundSprite->GetSize().y;

			for (int i = 0; i <= SCR_WIDTH / sizeX; i++)
			{
				for (int j = 0; j <= SCR_HEIGHT / sizeY; j++)
				{
					vec2 uvScale = vec2(1.0f, 1.0f);
					CORE_RenderCenteredSprite(vec2(i * sizeX + sizeX / 2, j * sizeY + sizeY / 2), vec2(sizeX, sizeY), backgroundSprite->GetTexture(), uvScale);
				}
			}
		}
		else
		{
			vec2 position = vec2(SCR_WIDTH / 2, SCR_HEIGHT / 2);
			vec2 size = background->GetTexture()->GetSize();
			vec2 uvScale = vec2(1.0f, 1.0f);
			CORE_RenderCenteredSprite(position, size, background->GetTexture()->GetTexture(), uvScale);
		}
	}
}

void RenderEngine::RenderSprites()
{
	for (Entity* entity : entities)
	{
		RenderComponent* renderComponent = entity->GetComponent<RenderComponent>();
		if (!renderComponent)
		{
			continue;
		}
		Sprite* sprite = renderComponent->GetTexture();
		if (sprite)
		{
			vec2 position = entity->GetPosition() + renderComponent->GetPositionOffset();
			vec2 entitySize = sprite->GetSize() * entity->GetScale();
			vec2 uvScale = vec2(1.0f, 1.0f);

			if (renderComponent->GetRenderMode() == RenderMode::Tiled)
			{
				uvScale = entitySize / sprite->GetSize();
			}
			CORE_RenderCenteredSprite(position, entitySize, sprite->GetTexture(), uvScale);
		}
	}
}

void RenderEngine::RenderUI()
{
	for (Widget* widget : widgets)
	{
		TextWidget* text = dynamic_cast<TextWidget*>(widget);
		if (text)
		{
			char textBuffer[50];
			snprintf(textBuffer, 50, "%s", text->GetText().c_str());
			FONT_DrawString(text->GetPosition(), textBuffer);
		}

		ImageWidget* image = dynamic_cast<ImageWidget*>(widget);
		if (image)
		{
			vec2 position = image->GetPosition();
			vec2 size = image->GetTexture()->GetSize() * image->GetScale();
			vec2 uvScale = vec2(1.0f, 1.0f);
			CORE_RenderCenteredSprite(position, size, image->GetTexture()->GetTexture(), uvScale);
		}

		CursorWidget* cursor = dynamic_cast<CursorWidget*>(widget);
		if (cursor)
		{
			vec2 position = cursor->GetPosition();
			vec2 size = cursor->GetTexture()->GetSize() * cursor->GetScale();
			vec2 uvScale = vec2(1.0f, 1.0f);
			CORE_RenderCenteredSprite(position, size, cursor->GetTexture()->GetTexture(), uvScale);
		}
	}
}

void RenderEngine::RegisterEntity(Entity* entity)
{
	entities.push_back(entity);
}

void RenderEngine::RegisterWidget(Widget* widget)
{
	widgets.push_back(widget);
}

void RenderEngine::RemoveEntity(Entity* entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void RenderEngine::RemoveWidget(Widget* widget)
{
	widgets.erase(std::remove(widgets.begin(), widgets.end(), widget), widgets.end());
}

void RenderEngine::ClearWidgets()
{
	widgets.clear();
}

Sprite* RenderEngine::CreateSprite(const std::string& name, const std::string& filePath, const bool& uvWrapping)
{
	Sprite* sprite = GetSprite(name, filePath, uvWrapping);
	if (!sprite)
	{
		unsigned int width, height;
		GLuint texture = CORE_LoadPNG(filePath.c_str(), uvWrapping, width, height);
		sprite = new Sprite(name, filePath, uvWrapping, vec2(width, height));
		sprite->SetTexture(texture);
	}
	sprite->IncrementRef();
	return sprite;
}

Sprite* RenderEngine::GetSprite(const std::string& name, const std::string& filePath, const bool& uvWrapping)
{
	for (Sprite* sprite : loadedSprites)
	{
		if (sprite->GetName() == name && sprite->GetFilePath() == filePath && sprite->GetWrapping() == uvWrapping)
		{
			return sprite;
		}
	}
	return nullptr;
}

void RenderEngine::UnloadSprite(Sprite* sprite)
{
	if (!sprite)
	{
		return;
	}

	if (sprite->CanDelete())
	{
		CORE_UnloadPNG(sprite->GetTexture());
		loadedSprites.erase(std::remove(loadedSprites.begin(), loadedSprites.end(), sprite), loadedSprites.end());
		delete(sprite);
	}
}

//GLuint RenderEngine::GetTexture(const char* filePath, bool uvWrapping, vec2& dimensions)
//{
//	TextureKey key{ filePath, uvWrapping };
//
//	auto iterator = loadedTextures.find(key);
//	if (iterator != loadedTextures.end())
//	{
//		return iterator->second; // Return texture ID
//	}
//	unsigned int width, height;
//
//	GLuint textureID = CORE_LoadPNG(filePath, uvWrapping, width, height);
//
//	dimensions.x = width;
//	dimensions.y = height;
//
//	loadedTextures[key] = textureID; // Store in loadedTextures
//
//	return textureID;
//}

void RenderEngine::UnloadAllSprites()
{
	for (Sprite* sprite : loadedSprites)
	{
		CORE_UnloadPNG(sprite->GetTexture());
		delete(sprite);
	}
}




