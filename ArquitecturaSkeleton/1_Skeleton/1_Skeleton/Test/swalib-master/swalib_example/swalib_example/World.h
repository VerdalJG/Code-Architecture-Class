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
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void Tick(float deltaTime);

private:
	std::vector<Entity*> entities;

public:
	std::vector<Entity*> GetEntities() { return entities; }
};

