#include "Background.h"
#include "Sprite.h"
#include "RenderManager.h"

Background::Background()
{
}

Background::~Background()
{
	if (sprite)
	{
		RenderManager::GetInstance().UnloadSprite(sprite);
	}
}
