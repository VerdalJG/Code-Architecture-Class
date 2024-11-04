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
	if (sprite)
	{
		RenderManager::GetInstance().UnloadSprite(sprite);
	}
}

void ImageWidget::SetSprite(Sprite* newSprite)
{
	if (sprite)
	{
		RenderManager::GetInstance().UnloadSprite(sprite);
	}
	sprite = newSprite;
	sprite->IncrementRef();
}
