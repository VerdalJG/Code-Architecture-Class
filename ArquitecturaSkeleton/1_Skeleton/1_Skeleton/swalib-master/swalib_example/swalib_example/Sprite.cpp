#include "Sprite.h"
#include "Render.h"

Sprite::Sprite(GLuint textureID, vec2 SpriteSize)
{
	texture = textureID;
	SetSize(SpriteSize);
}

Sprite::~Sprite()
{

}

void Sprite::SetTexture(const char* FilePath, bool ScreenWrapping)
{
	GLuint NewTexture = RenderEngine::GetInstance().LoadTexture(FilePath, ScreenWrapping);
	texture = NewTexture;
}
