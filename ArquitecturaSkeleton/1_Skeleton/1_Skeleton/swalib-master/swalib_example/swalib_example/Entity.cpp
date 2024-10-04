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

void Entity::CreateSprite(const char* filePath, bool screenWrapping, vec2 spriteSize)
{
	sprite = new Sprite(filePath, screenWrapping, spriteSize);
}

World* Entity::GetWorld()
{
	return GameManager::GetInstance().world;
}

void Entity::SetPosition(vec2 NewPosition)
{
	position = NewPosition;
}
