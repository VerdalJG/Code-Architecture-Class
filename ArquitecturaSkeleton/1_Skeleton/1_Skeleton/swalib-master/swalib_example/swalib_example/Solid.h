#pragma once
#include "Globals.h"
#include "Component.h"
#include "Entity.h"

class Sprite;
class World;

class Solid : public Entity
{
public:
	Solid();
	virtual ~Solid() override;

	virtual void OnCollide(Entity* other);
};

