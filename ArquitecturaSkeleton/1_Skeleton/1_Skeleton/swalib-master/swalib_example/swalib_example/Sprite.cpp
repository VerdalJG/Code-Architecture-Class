#include "Sprite.h"
#include "Render.h"

Sprite::Sprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize)
{
	texture = RenderEngine::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	SetSize(SpriteSize);
	offset = vec2(0, 0);
}

Sprite::~Sprite()
{
	RenderEngine::GetInstance().UnloadSprite(texture);
}

void Sprite::SetTexture(const char* FilePath, bool ScreenWrapping)
{
	RenderEngine::GetInstance().UnloadSprite(texture);
	GLuint NewTexture = RenderEngine::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	texture = NewTexture;
}
