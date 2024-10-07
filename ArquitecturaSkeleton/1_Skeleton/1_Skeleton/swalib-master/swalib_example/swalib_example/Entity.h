#pragma once
#include "Globals.h"

class Sprite;
class World;
class Component;
class Message;

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Tick(float deltaTime);
	void AddComponent(Component* component);
	
	template<typename T>
	T* GetComponent();
	void BroadcastMessage(Message* message);

protected:

	void CreateSprite(GLuint textureID, vec2 spriteSize);
	World* GetWorld();

	vec2 position;
	vec2 scale;
	
public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 newPosition);

	vec2 GetScale() { return scale; }
	void SetScale(vec2 newScale) { scale = newScale; }

	Sprite* GetSprite() { return sprite; }

private:
	Sprite* sprite;
	std::vector<Component*> components;


};

