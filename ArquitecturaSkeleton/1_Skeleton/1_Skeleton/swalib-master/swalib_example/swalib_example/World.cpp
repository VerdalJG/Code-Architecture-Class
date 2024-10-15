#include "World.h"
#include "Timer.h"
#include "Sprite.h"
#include "Render.h"
#include "Entity.h"
#include "Background.h"


World::World()
{
	worldType = WorldType::None;
	background = new Background();
}

void World::Terminate()
{
	if (background)
	{
		delete(background);
	}
	for (Entity* entity : entities)
	{
		delete(entity);
	}
	for (Widget* widget : widgets)
	{
		delete(widget);
	}
}

void World::AddEntity(Entity* entity)
{
	if (entity)
	{
		entities.push_back(entity);
		RenderEngine::GetInstance().RegisterEntity(entity);
	}
}

void World::RemoveEntity(Entity* entity)
{
	if (entity)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		delete(entity);
	}
}

void World::AddWidget(Widget* widget)
{
	if (widget)
	{
		widgets.push_back(widget);
		RenderEngine::GetInstance().RegisterWidget(widget);
	}
}

void World::RemoveWidget(Widget* widget)
{
	if (widget)
	{
		widgets.erase(std::remove(widgets.begin(), widgets.end(), widget), widgets.end());
		delete(widget);
	}
}

void World::Tick(float deltaTime)
{
	for (Entity* entity : entities)
	{
		entity->Tick(deltaTime);
	}
}

void World::SetBackground(Background* newBackground)
{
	if (background)
	{
		delete(background);
	}
	background = newBackground;
}
