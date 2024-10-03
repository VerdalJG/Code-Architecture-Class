#pragma once
#include "Globals.h"

class Entity;
class Sprite;
class TimeManager; 

class World
{
public:
	World();
	void Terminate();
	void AddEntity(Entity* Entity);
	void RemoveEntity(Entity* Entity);
	void Tick(float DeltaTime);

private:
	std::vector<Entity*> entities;

public:
	std::vector<Entity*> GetEntities() { return entities; }
};

