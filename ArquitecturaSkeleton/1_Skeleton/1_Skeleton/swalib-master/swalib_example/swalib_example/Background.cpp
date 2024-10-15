#include "Background.h"
#include "Render.h"
#include "Sprite.h"

Background::Background()
{
}

Background::~Background()
{
	if (sprite)
	{
		delete(sprite);
	}
}

void Background::SetSprite(const char* filePath, bool screenWrapping)
{
	sprite = new Sprite(filePath, screenWrapping, vec2(128.0f, 128.0f));
}
