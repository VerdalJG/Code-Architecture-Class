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
	void AddComponents(std::vector<Component*> components);
	
	void BroadcastMessage(Message* message);
	virtual void OnCollide(Entity* other) {};
	virtual void OnTrigger(Entity* other) {};
	void AttachToEntity(Entity* parentEntity);
	void RegisterChild(Entity* child);
	void Destroy();


protected:
	World* GetWorld();
	void UpdateWorldTransform();

	Entity* parent = nullptr;
	std::vector<Entity*> children;
	std::vector<Component*> components;
	std::string name;
	vec2 localPosition;
	vec2 worldPosition;
	vec2 localScale;
	vec2 worldScale;

	bool markedForDestruction = false;


public:
	vec2 GetWorldPosition() { return worldPosition; }
	void SetWorldPosition(const vec2& newPosition);

	vec2 GetWorldScale() { return worldScale; }
	void SetWorldScale(const vec2& newScale);

	vec2 GetLocalPosition() { return localPosition; }
	void SetLocalPosition(vec2 newLocalPosition);

	vec2 GetLocalScale() { return localScale; }
	void SetLocalScale(vec2 newScale);

	std::vector<Component*> GetAllComponents() { return components; }

	bool ShouldDestroy() { return markedForDestruction; }

	std::string GetName() { return name; }
	void SetName(std::string newName) { name = newName; }

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

	template<typename T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> result;
		for (Component* component : components)
		{
			if (T* derivedComponent = dynamic_cast<T*>(component))
			{
				result.push_back(derivedComponent);
			}
		}
		return result;
	}
};

