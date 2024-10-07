#include "Entity.h"
#include "GameManager.h"
#include "Sprite.h"
#include "Globals.h"
#include "Component.h"

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

void Entity::Tick(float deltaTime)
{
	for (Component* component : components)
	{
		component->Tick(deltaTime);
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

void Entity::CreateSprite(GLuint textureID, vec2 spriteSize)
{
	sprite = new Sprite(textureID, spriteSize);
}

World* Entity::GetWorld()
{
	return GameManager::GetInstance().world;
}

void Entity::SetPosition(vec2 NewPosition)
{
	position = NewPosition;
}

// Normally game engines do not use RTTI, should use different methods other than dynamic_cast for performance
template<typename T>
T* Entity::GetComponent()
{
	for (Component* component : components)
	{
		if (T* derivedComponent = dynamic_cast<T*>(component))
		{
			return derivedComponent;
		}
	}
	return nullptr;
}
