#include "Background.h"
#include "Render.h"
#include "Sprite.h"

Background::Background()
{
	sprite = new Sprite(RenderEngine::GetInstance().backgroundTexture, vec2(128.0f, 128.0f));
}

Background::~Background()
{
	if (sprite)
	{
		delete(sprite);
	}
}
