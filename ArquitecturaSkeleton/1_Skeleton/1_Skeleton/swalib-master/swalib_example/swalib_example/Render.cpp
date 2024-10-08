#include "Render.h"
#include "Globals.h"
#include "Timer.h"
#include "Sprite.h"
#include "Entity.h"
#include "Background.h"

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
	vec2 spriteSize = vec2(128.0f, 128.0f);

	backgroundTexture = LoadTexture("data/circle-bkg-128.png", true);
	ballTexture = LoadTexture("data/tyrian_ball.png", false);

	background = new Background();
}

void RenderEngine::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.
	
	RenderTiled(background->sprite);
	RenderSprites();
	DisplayTimerValues();

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

void RenderEngine::Terminate()
{
	// Unload font.
	UnloadTextures();
	FONT_End();
	delete(background);
}

void RenderEngine::RenderTiled(Sprite* sprite)
{
	// Render tiled image
	int sizeX = sprite->GetSize().x;
	int sizeY = sprite->GetSize().y;

	for (int i = 0; i <= SCR_WIDTH / sizeX; i++)
	{
		for (int j = 0; j <= SCR_HEIGHT / sizeY; j++) {
			CORE_RenderCenteredSprite(vec2(i * sizeX + sizeX/2, j * sizeY + sizeY/2), vec2(sizeX, sizeY), sprite->GetTexture());
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
		Sprite* sprite = renderComponent->GetSprite();
		if (sprite)
		{
			vec2 position = entity->GetPosition() + renderComponent->GetPositionOffset();
			vec2 size = sprite->GetSize() * entity->GetScale();
			CORE_RenderCenteredSprite(position, size, sprite->GetTexture());
		}

	}
}

void RenderEngine::RegisterEntity(Entity* entity)
{
	entities.push_back(entity);
}

GLuint RenderEngine::LoadTexture(const char* filePath, bool screenWrapping)
{
	return CORE_LoadPNG(filePath, screenWrapping);
}

void RenderEngine::UnloadTextures()
{
	CORE_UnloadPNG(ballTexture);
	CORE_UnloadPNG(backgroundTexture);
}




