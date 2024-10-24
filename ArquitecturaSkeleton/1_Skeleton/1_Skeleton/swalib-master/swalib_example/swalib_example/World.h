#pragma once
#include "Globals.h"

class Entity;
class Actor;
class Solid;
class Sprite;
class TimeManager; 
class Background;
class Widget;
class Player;

class World
{
public:
	World();
	void Terminate();
	void AddActor(Actor* actor);
	void RemoveEntity(Actor* actor);

	void AddSolid(Solid* solid);
	void RemoveSolid(Solid* solid);

	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);

	void Tick(float deltaTime);
	void ProcessInputs();

private:
	std::vector<Solid*> solids;
	std::vector<Actor*> actors;
	std::vector<Entity*> entities;
	Background* background;
	Player* player;


public:
	std::vector<Entity*> GetEntities() { return entities; }

	Background* GetBackground() { return background; }
	void SetBackground(Background* newBackground);
};

