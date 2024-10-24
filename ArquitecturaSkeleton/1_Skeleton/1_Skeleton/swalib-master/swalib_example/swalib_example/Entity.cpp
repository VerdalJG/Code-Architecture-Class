#include "Entity.h"
#include "GameManager.h"
#include "Sprite.h"
#include "Globals.h"
#include "Component.h"
#include "WorldManager.h"

Entity::Entity() :
	scale(vec2(1, 1)),
	position(vec2(0,0))
{
}

Entity::~Entity()
{
	for (Component* component : components)
	{
		delete(component);
	}
}

void Entity::AddComponent(Component* component)
{
	if (component)
	{
		component->owner = this;
		components.push_back(component);
	}
}

void Entity::BroadcastMessage(Message* message)
{
	for (Component* component : components)
	{
		component->ReceiveMessage(message);
	}
}

World* Entity::GetWorld()
{
	return WorldManager::GetInstance().GetCurrentWorld();
}
