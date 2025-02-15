#pragma once
#include "Globals.h"

class Entity;
class Ball;
class TimeManager;
class World;

class GameManager
{
public:
	static GameManager& GetInstance();
	void Initialize(TimeManager* timer);
	void Slot();
	void Tick(float deltaTime);
	void Terminate();

public:
	World* world;
	const unsigned int NUM_BALLS = 10;	// Max. num balls.

private:
	const char* jsonFilePath = "data/BallSetup.json";
	TimeManager* timer;
};


