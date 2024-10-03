#include "Entity.h"
#include "GameManager.h"
#include "Sprite.h"
#include "Globals.h"

Entity::Entity() :
	MySprite(nullptr),
	Scale(vec2(1, 1)),
	Position(vec2(0,0))
{
	GameManager::GetInstance().RegisterEntity(this);
}

Entity::~Entity()
{
	if (MySprite)
	{
		delete(MySprite);
	}
}

void Entity::CreateSprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize)
{
	MySprite = new Sprite(FilePath, ScreenWrapping, SpriteSize);
}

void Entity::SetPosition(vec2 NewPosition)
{
	Position = NewPosition;
}
