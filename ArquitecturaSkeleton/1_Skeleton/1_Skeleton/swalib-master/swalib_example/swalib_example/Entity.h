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
	virtual void Tick(float deltaTime);
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

protected:
	World* GetWorld();

	std::vector<Component*> components;
	vec2 position;
	vec2 scale;
	
public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 newPosition);

	vec2 GetScale() { return scale; }
	void SetScale(vec2 newScale) { scale = newScale; }

private:




};

