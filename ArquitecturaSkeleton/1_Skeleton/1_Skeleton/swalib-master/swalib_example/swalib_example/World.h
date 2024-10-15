#pragma once
#include "Globals.h"

class Entity;
class Sprite;
class TimeManager; 
class Background;
class Widget;

enum class WorldType
{
	None,
	MainMenu,
	Level1,
	Level2
};

class World
{
public:
	World();
	void Terminate();
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);
	void Tick(float deltaTime);

private:
	WorldType worldType;
	std::vector<Entity*> entities;
	std::vector<Widget*> widgets;
	Background* background; 


public:
	std::vector<Entity*> GetEntities() { return entities; }

	WorldType GetWorldType() { return worldType; }
	void SetWorldType(WorldType type) { worldType = type; }

	Background* GetBackground() { return background; }
	void SetBackground(Background* newBackground);
};

