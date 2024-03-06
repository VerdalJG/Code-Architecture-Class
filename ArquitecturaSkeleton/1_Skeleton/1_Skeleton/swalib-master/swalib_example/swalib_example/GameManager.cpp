#include "GameManager.h"

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

void GameManager::Slot()
{
	_timer.UpdateTime();
	while (_timer.Tick())
	{
		LogicSlot(_timer.GetFixedTickRate());
	}
}

void GameManager::LogicSlot(float deltaTime)
{
	for (Ball* ball : balls)
	{
		ball->Slot(deltaTime);
	}
}

void GameManager::Terminate()
{
}

void GameManager::Initialize()
{
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) 
	{
		/*balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
		balls[i].radius = 16.f;
		balls[i].gfx = texsmallball;*/
	}
}
