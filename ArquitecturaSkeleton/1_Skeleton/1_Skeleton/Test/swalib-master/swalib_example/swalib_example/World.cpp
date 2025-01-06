#include "World.h"
#include "Timer.h"
#include "Sprite.h"
#include "Render.h"
#include "Entity.h"


World::World()
{

}

void World::Terminate()
{

}

void World::AddEntity(Entity* entity)
{
	entities.push_back(entity);
	RenderEngine::GetInstance().RegisterEntity(entity);
}

void World::RemoveEntity(Entity* entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	delete(entity);
}

void World::Tick(float deltaTime)
{
	for (Entity* entity : entities)
	{
		entity->Tick(deltaTime);
	}
}
