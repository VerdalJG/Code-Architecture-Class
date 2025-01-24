#pragma once
#include "Globals.h"
#include "Component.h"
#include <unordered_map>
#include <typeindex>

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

	// Mapping type id to a vector of components, allowing multiple components of the same type (e.g. box and circle collider)
	std::unordered_map<std::type_index, std::vector<Component*>> components;
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

	std::vector<Component*> GetAllComponents() 
	{ 
		std::vector<Component*> result;
		for (auto iterator = components.begin(); iterator != components.end(); ++iterator)
		{
			const std::vector<Component*>& componentList = iterator->second;
			result.insert(result.end(), componentList.begin(), componentList.end());
		}

		return result;
	}

	bool ShouldDestroy() { return markedForDestruction; }

	std::string GetName() { return name; }
	void SetName(std::string newName) { name = newName; }

	template<typename T>
	T* GetComponent()
	{
		auto iterator = components.find(std::type_index(typeid(T)));
		if (iterator != components.end())
		{
			return static_cast<T*>(iterator->second.front());
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetComponents()
	{
		auto iterator = components.find(std::type_index(typeid(T)));
		if (iterator != components.end())
		{
			return static_cast<std::vector<T*>>(iterator->second);
		}
		return nullptr;
	}
};

