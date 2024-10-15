#include "ImageWidget.h"
#include "Globals.h"

ImageWidget::ImageWidget() :
	sprite(nullptr),
	scale(vec2(0,0))
{
}

ImageWidget::~ImageWidget()
{
	if (sprite)
	{
		delete(sprite);
	}
}

void ImageWidget::SetSprite(Sprite* newSprite)
{
	if (sprite)
	{
		delete(sprite);
	}
	sprite = newSprite;
}
