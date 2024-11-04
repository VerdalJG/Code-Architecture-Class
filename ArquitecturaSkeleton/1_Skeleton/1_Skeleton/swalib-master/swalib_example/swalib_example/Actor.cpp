#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Tick(float deltaTime)
{
	for (Component* component : components)
	{
		component->Tick(deltaTime);
	}
}
