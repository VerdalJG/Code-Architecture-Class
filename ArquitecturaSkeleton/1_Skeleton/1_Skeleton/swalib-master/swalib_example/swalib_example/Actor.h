#pragma once
#include "Globals.h"
#include "Entity.h"

class Actor : public Entity
{
public:
	virtual void Tick(float deltaTime);
	virtual void OnCollide(Entity* other) {};
};

