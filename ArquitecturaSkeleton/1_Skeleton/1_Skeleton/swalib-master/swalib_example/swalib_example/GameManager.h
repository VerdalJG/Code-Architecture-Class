#pragma once
#include "Globals.h"

class Entity;
class Ball;
class Timer;

class GameManager
{
public:
	static GameManager& GetInstance();
	void Initialize();
	void Slot();
	void Tick(float DeltaTime);
	void Terminate();
	void CollisionCheck();
	void RegisterEntity(Entity* Entity);

public:
	std::vector<Entity*> Entities;
	std::vector<Ball*> Balls;
	const unsigned int NUM_BALLS = 10;	// Max. num balls.

private:
	Timer* Timer;
};


