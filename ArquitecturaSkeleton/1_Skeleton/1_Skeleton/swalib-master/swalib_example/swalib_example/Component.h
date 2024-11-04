#pragma once
class Entity;
class Message;
class World;

class Component
{
public:
	Entity* owner;

	virtual void Tick(float deltaTime) {};
	virtual ~Component() = default; // compiler generates a default destructor, slightly more optimal
	virtual void OnAttach() {};
	virtual Component* Clone() { return nullptr; };
	World* GetWorld();


	virtual void ReceiveMessage(Message* message) {};
};

