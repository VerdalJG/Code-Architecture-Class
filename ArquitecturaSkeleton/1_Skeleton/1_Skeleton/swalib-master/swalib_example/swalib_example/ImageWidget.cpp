#include "ImageWidget.h"
#include "Globals.h"
#include "RenderManager.h"

ImageWidget::ImageWidget() :
	sprite(nullptr),
	scale(vec2(0,0))
{
}

ImageWidget::~ImageWidget()
{
	if (sprite)
	{
		RenderEngine::GetInstance().UnloadSprite(sprite);
	}
}

void ImageWidget::SetSprite(Sprite* newSprite)
{
	if (sprite)
	{
		RenderEngine::GetInstance().UnloadSprite(sprite);
	}
	sprite = newSprite;
}
