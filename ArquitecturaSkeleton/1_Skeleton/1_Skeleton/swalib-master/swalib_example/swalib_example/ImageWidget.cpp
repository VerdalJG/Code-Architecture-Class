#include "ImageWidget.h"
#include "Globals.h"
#include "RenderManager.h"
#include "Sprite.h"

ImageWidget::ImageWidget() :
	sprite(nullptr),
	scale(vec2(0,0))
{
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::SetSprite(Sprite* newSprite)
{
	sprite = newSprite;
}
