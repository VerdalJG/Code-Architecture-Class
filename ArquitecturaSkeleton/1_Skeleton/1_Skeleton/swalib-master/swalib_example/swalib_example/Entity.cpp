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
	for (auto& pair : components)
	{
		for (Component* component : pair.second)
		{
			delete(component);
		}
		pair.second.clear();
	}
	components.clear();
}

void Entity::AddComponent(Component* component)
{
	if (component)
	{
		component->owner = this;
		component->OnAttach();

		// Use std::type_index of the component's dynamic type as the key
		std::type_index type = typeid(*component);

		// Add the component to the corresponding vector in the map
		components[type].push_back(component);
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

			// Use std::type_index of the component's dynamic type as the key
			std::type_index type = typeid(*component);

			// Add the component to the corresponding vector in the map
			this->components[type].push_back(component);
		}
	}
}

void Entity::BroadcastMessage(Message* message)
{
	for (const auto& pair : components)
	{
		for (Component* component : pair.second)
		{
			component->ReceiveMessage(message);
		}
	}

	for (Entity* child : children)
	{
		for (const auto& pair : child->components)
		{
			for (Component* childComponent : pair.second) // Iterate over the child's components vector
			{
				childComponent->ReceiveMessage(message);
			}
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