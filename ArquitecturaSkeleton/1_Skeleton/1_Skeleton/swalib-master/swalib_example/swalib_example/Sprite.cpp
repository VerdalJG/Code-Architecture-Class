#include "Sprite.h"
#include "Render.h"

Sprite::Sprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize)
{
	Texture = RenderEngine::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	SetSize(SpriteSize);
	Offset = vec2(0, 0);
}

Sprite::~Sprite()
{
	RenderEngine::GetInstance().UnloadSprite(Texture);
}

void Sprite::SetTexture(const char* FilePath, bool ScreenWrapping)
{
	RenderEngine::GetInstance().UnloadSprite(Texture);
	GLuint NewTexture = RenderEngine::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	Texture = NewTexture;
}
