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
	void Initialize(TimeManager* _Timer);
	void Slot();
	void Tick(float DeltaTime);
	void Terminate();
	void CollisionCheck();

public:
	World* world;
	const unsigned int NUM_BALLS = 10;	// Max. num balls.

private:
	TimeManager* timer;
};


