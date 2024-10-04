#include "Entity.h"
#include "GameManager.h"
#include "Sprite.h"
#include "Globals.h"

Entity::Entity() :
	sprite(nullptr),
	scale(vec2(1, 1)),
	position(vec2(0,0))
{
}

Entity::~Entity()
{
	if (sprite)
	{
		delete(sprite);
	}
}

void Entity::CreateSprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize)
{
	sprite = new Sprite(FilePath, ScreenWrapping, SpriteSize);
}

World* Entity::GetWorld()
{
	return GameManager::GetInstance().world;
}

void Entity::SetPosition(vec2 NewPosition)
{
	position = NewPosition;
}
