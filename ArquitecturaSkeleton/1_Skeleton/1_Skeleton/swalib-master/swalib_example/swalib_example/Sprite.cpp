#include "Sprite.h"
#include "Render.h"

Sprite::Sprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize)
{
	Texture = Renderer::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	SetSize(SpriteSize);
	Offset = vec2(0, 0);
}

Sprite::~Sprite()
{
}

void Sprite::SetTexture(const char* FilePath, bool ScreenWrapping)
{
	Renderer::GetInstance().UnloadSprite(Texture);
	GLuint NewTexture = Renderer::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	Texture = NewTexture;
}
