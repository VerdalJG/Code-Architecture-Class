#include "Entity.h"
#include "GameManager.h"
#include "Sprite.h"
#include "Globals.h"
#include "Component.h"
#include "WorldManager.h"
#include "MovementMessage.h"

Entity::Entity() :
	localScale(vec2(1, 1)),
	worldPosition(vec2(0,0))
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
		component->OnAttach();
		components.push_back(component);
	}
}

void Entity::AddComponents(std::vector<Component*> components)
{
	for (Component* component : components)
	{
		if (component)
		{
			component->owner = this;
			component->OnAttach();
			components.push_back(component);
		}
	}
}

void Entity::BroadcastMessage(Message* message)
{
	for (Component* component : components)
	{
		component->ReceiveMessage(message);
	}
	for (Entity* child : children)
	{
		for (Component* childComponent : child->components)
		{
			childComponent->ReceiveMessage(message);
		}
	}
}

void Entity::AttachToEntity(Entity* parentEntity)
{
	parent = parentEntity;
}

void Entity::RegisterChild(Entity* child)
{
	children.push_back(child);
}

void Entity::Destroy()
{
	markedForDestruction = true;
}

World* Entity::GetWorld()
{
	return WorldManager::GetInstance().GetCurrentWorld();
}

void Entity::SetWorldPosition(const vec2& newPosition)
{
	if (parent) 
	{
		localPosition = (newPosition - parent->worldPosition) / parent->worldScale;
	}
	else 
	{
		localPosition = newPosition;
	}
	UpdateWorldTransform(); // Update world positions for this entity and its children
}

void Entity::SetWorldScale(const vec2& newScale)
{
	if (parent) 
	{
		localScale = newScale / parent->worldScale;
	}
	else 
	{
		localScale = newScale;
	}
	UpdateWorldTransform(); // Update world scales for this entity and its children
}

void Entity::SetLocalPosition(vec2 newLocalPosition)
{
	localPosition = newLocalPosition;
	UpdateWorldTransform();
}

void Entity::SetLocalScale(vec2 newScale)
{
	localScale = newScale;
	UpdateWorldTransform();
}

void Entity::UpdateWorldTransform()
{
	if (parent) 
	{
		worldPosition = parent->GetWorldPosition() + parent->GetWorldScale() * localPosition;
		worldScale = parent->worldScale * localScale;
	}
	else 
	{
		worldPosition = localPosition;
		worldScale = localScale;
	}

	MovementMessage message = MovementMessage(worldPosition);
	BroadcastMessage(&message);

	// Update children
	for (Entity* child : children) 
	{
		child->UpdateWorldTransform();
	}
}