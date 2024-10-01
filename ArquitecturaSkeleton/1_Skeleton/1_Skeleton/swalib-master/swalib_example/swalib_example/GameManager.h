#pragma once
#include "../../common/stdafx.h"
#include "../../common/core.h"
#include "../../common/sys.h"
#include "../../common/font.h"
#include "../../common/vector2d.h"
#include "Timer.h"

class Ball;

class GameManager
{

public:
	static GameManager& GetInstance();
	void Initialize();
	void Slot();
	void Tick(float deltaTime);
	void Terminate();
	void CollisionCheck();

public:
	std::vector<Ball*> Balls;
	const unsigned int NUM_BALLS = 10;	// Max. num balls.

private:
	Timer Timer;
};


