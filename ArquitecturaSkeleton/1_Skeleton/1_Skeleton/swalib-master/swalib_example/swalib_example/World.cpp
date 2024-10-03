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

void World::AddEntity(Entity* _entity)
{
	entities.push_back(_entity);
	RenderEngine::GetInstance().RegisterEntity(_entity);
}

void World::RemoveEntity(Entity* _entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), _entity), entities.end());
}

void World::Tick(float _deltaTime)
{
	for (Entity* entity : entities)
	{
		entity->Tick(_deltaTime);
	}
}
