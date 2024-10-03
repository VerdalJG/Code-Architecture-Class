#include "World.h"
#include "Timer.h"
#include "Sprite.h"


World::World()
{

}

void World::Terminate()
{

}

void World::AddEntity(Entity* Entity)
{
	Entities.push_back(Entity);
}

void World::RemoveEntity(Entity* Entity)
{
	Entities.erase(std::remove(Entities.begin(), Entities.end(), Entity), Entities.end());
}

void World::Tick(float DeltaTime)
{
	for (Entity* Entity : Entities)
	{

	}
}
