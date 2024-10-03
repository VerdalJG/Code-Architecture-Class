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
	vec2 SpriteSize = vec2(128.0f, 128.0f);
	background = new Background();
	background->sprite = new Sprite("data/circle-bkg-128.png", true, SpriteSize);
}

void RenderEngine::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.
	
	RenderTiled(background->sprite);
	DisplayTimerValues();

	RenderSprites();

	// Exchanges the front and back buffers
	SYS_Show();
}

void RenderEngine::DisplayTimerValues()
{
	// Buffers for strings below
	char FPSBuffer[50];
	char realTimeBuffer[50];
	char logicTimeBuffer[50];

	// Concatenate string with numbers
	snprintf(FPSBuffer, 50, "FPS: %f", timer->GetFPS());
	snprintf(realTimeBuffer, 50, "RT: %f", timer->GetTime());
	snprintf(logicTimeBuffer, 50, "LT: %f", timer->GetLogicTime());

	// Text
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 50), FPSBuffer);
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 70), realTimeBuffer);
	FONT_DrawString(vec2(SCR_WIDTH - 600, SCR_HEIGHT - 90), logicTimeBuffer);
}

void RenderEngine::Terminate()
{
	// Unload font.
	FONT_End();
	delete(background);
}

void RenderEngine::RenderTiled(Sprite* _sprite)
{
	// Render tiled image
	int SizeX = _sprite->GetSize().x;
	int SizeY = _sprite->GetSize().y;

	for (int i = 0; i <= SCR_WIDTH / SizeX; i++)
	{
		for (int j = 0; j <= SCR_HEIGHT / SizeY; j++) {
			CORE_RenderCenteredSprite(vec2(i * SizeX + SizeX/2, j * SizeY + SizeY/2), vec2(SizeX, SizeY), _sprite->GetTexture());
		}
	}
}

void RenderEngine::RenderSprites()
{
	for (Entity* Entity : entities)
	{
		Sprite* Sprite = Entity->GetSprite();
		vec2 Position = Entity->GetPosition() + Sprite->GetOffset();
		vec2 Size = Sprite->GetSize() * Entity->GetScale();
		CORE_RenderCenteredSprite(Position, Size, Sprite->GetTexture());
	}
}

void RenderEngine::RegisterEntity(Entity* _entity)
{
	entities.push_back(_entity);
}

GLuint RenderEngine::LoadSprite(const char* FilePath, bool ScreenWrapping)
{
	return CORE_LoadPNG(FilePath, ScreenWrapping);
}

void RenderEngine::UnloadSprite(GLuint TextureID)
{
	CORE_UnloadPNG(TextureID);
}




