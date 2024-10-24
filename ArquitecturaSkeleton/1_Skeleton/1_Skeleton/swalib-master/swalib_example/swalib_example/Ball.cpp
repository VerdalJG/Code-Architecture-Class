#include "Ball.h"
#include "Globals.h"
#include "World.h"
#include "Sprite.h"

Ball::Ball()
{
}

Ball::~Ball()
{
	
}

void Ball::Tick(const float deltaTime)
{
	for (Component* component : components)
	{
		component->Tick(deltaTime);
	}
}


