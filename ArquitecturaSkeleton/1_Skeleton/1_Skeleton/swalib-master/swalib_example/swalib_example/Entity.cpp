#include "Entity.h"
#include "GameManager.h"

Entity::Entity() :
	Sprite(nullptr)
{
	GameManager::GetInstance().RegisterEntity(this);
}

Entity::~Entity()
{
	if (Sprite)
	{
		delete(Sprite);
	}
}
