#pragma once
#include "Globals.h"
#include "Component.h"

class Sprite;
class World;
class Component;
class Message;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	void AddComponent(Component* component);
	
	// Normally game engines do not use RTTI, should use different methods other than dynamic_cast for performance
	template<typename T>
	T* GetComponent()
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

	void BroadcastMessage(Message* message);
	virtual void OnCollide(Entity* other) {};

protected:
	World* GetWorld();

	std::vector<Component*> components;
	vec2 position;
	vec2 scale;
	std::string name;

public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 newPosition) { position = newPosition; }

	vec2 GetScale() { return scale; }
	void SetScale(vec2 newScale) { scale = newScale; }

	std::string GetName() { return name; }
	void SetName(std::string newName) { name = newName; }
};

