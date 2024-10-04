#include "Background.h"
#include "Render.h"
#include "Sprite.h"

Background::Background() :
	sprite(nullptr)
{

}

Background::~Background()
{
	if (sprite)
	{
		delete(sprite);
	}
}
