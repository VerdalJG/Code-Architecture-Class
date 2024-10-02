#include "Sprite.h"
#include "Render.h"

GLuint Sprite::SetTexture(GLuint NewTexture)
{
	Texture = NewTexture;
	if (Texture != 0)
	{
		Renderer::GetInstance().LoadSprite()
	}
}
