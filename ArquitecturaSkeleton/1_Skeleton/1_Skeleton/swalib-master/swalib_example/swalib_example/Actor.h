#pragma once
#include "Globals.h"
#include "Entity.h"

class Actor : public Entity
{
public:
	Actor();
	virtual ~Actor() override;

	virtual void BeginPlay() {};
	virtual void Tick(float deltaTime);
	virtual void OnCollide(Entity* other) {};
	virtual void OnTrigger(Entity* other) {};
};

