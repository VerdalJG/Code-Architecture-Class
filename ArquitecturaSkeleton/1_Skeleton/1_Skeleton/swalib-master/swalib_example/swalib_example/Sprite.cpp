#include "Sprite.h"
#include "Render.h"

Sprite::Sprite(GLuint textureID, vec2 SpriteSize)
{
	texture = textureID;
	SetSize(SpriteSize);
	offset = vec2(0, 0);
}

Sprite::~Sprite()
{

}

void Sprite::SetTexture(const char* FilePath, bool ScreenWrapping)
{
	GLuint NewTexture = RenderEngine::GetInstance().LoadSprite(FilePath, ScreenWrapping);
	texture = NewTexture;
}
