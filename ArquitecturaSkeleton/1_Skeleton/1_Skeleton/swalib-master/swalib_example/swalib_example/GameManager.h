#pragma once
#include "Globals.h"
#include "Ball.h"

class GameManager
{

public:
	static GameManager* GetInstance();
	void LogicSlot(float deltaTime);

	std::vector<Ball*> balls;

private:
	static GameManager* _instance;

};

void InitGame()
{
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
		balls[i].radius = 16.f;
		balls[i].gfx = texsmallball;
	}
}

void UpdateGame(float deltaTime)
{
	for (Ball ball : balls)
	{
		ball.Slot(deltaTime);
	}
	
}