#pragma once
#include "Globals.h"

class World;
class Wall;
class Sprite;

enum class WorldType 
{
	MainMenu,
	GameWorld
};

class WorldManager
{
public:
	static WorldManager& GetInstance();
	void Initialize();
	void Terminate();
	void LoadWorld(WorldType worldType);
	void LoadGameWorld();
	void UnloadCurrentWorld();
	void CreateBorders(World* world);
	void CreatePlayer(World* world);
	void CreateHarpoon(World* world);
	void CreateBalls(World* world);
	Wall* CreateWall(const std::string& name, const vec2& scale, const vec2& worldPosition, Sprite* sprite, World* world);
	void CreateGameUI(World* world);

	void LoadMainMenu();
	World* GetCurrentWorld();

private:
	void LoadLevel(int level);

	World* currentWorld = nullptr;
	World* mainMenuWorld = nullptr;
	World* gameWorld = nullptr;

	WorldType currentWorldType;

	const unsigned int NUM_BALLS = 10;	// Max. num balls.
};

