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
	void ExitGame();
	void AddScore() { score += 10; }
	

private:
	const char* jsonFilePath = "data/BallSetup.json";
	int score;
	TimeManager* timer;
	
};


