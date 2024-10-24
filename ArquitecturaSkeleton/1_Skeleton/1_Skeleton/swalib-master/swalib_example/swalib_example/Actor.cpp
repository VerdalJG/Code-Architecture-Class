#include "Actor.h"

void Actor::Tick(float deltaTime)
{
	for (Component* component : components)
	{
		component->Tick(deltaTime);
	}
}
