#include "Sprite.h"
#include "Render.h"

Sprite::Sprite(const char* filePath, bool screenWrapping, vec2 SpriteSize)
{
	SetTexture(filePath, screenWrapping);
	SetSize(SpriteSize);
}

Sprite::~Sprite()
{

}

void Sprite::SetTexture(const char* filePath, bool screenWrapping)
{
	GLuint NewTexture = RenderEngine::GetInstance().GetTexture(filePath, screenWrapping);
	texture = NewTexture;
}
