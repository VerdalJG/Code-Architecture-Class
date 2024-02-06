#pragma once
#include "Globals.h"
#include "Ball.h"
#include "Timer.h"

class GameManager
{

public:
	static GameManager& GetInstance();

	void Initialize();
	void LogicSlot(float deltaTime);
	std::vector<Ball*> balls;

private:
	Timer _timer;
};


