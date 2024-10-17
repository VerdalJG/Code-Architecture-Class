#pragma once
#include "Globals.h"

class World;

class WorldManager
{
public:
	static WorldManager& GetInstance();
	void Initialize();
	void Terminate();
	void LoadWorld(int world);
	void LoadLevel(int level);
	void LoadMainMenu();
	World* GetCurrentWorld();

private:
	std::vector<World*> worlds;
	unsigned int currentWorldIndex = -1;
	const unsigned int NUM_BALLS = 10;	// Max. num balls.
};

