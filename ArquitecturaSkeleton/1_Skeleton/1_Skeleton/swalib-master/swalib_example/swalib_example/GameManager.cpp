#include "GameManager.h"
#include "Ball.h"

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

void GameManager::Slot()
{
	Timer.UpdateTime();
	while (Timer.Tick())
	{
		LogicSlot(Timer.GetFixedTickRate());
	}
}

void GameManager::LogicSlot(float deltaTime)
{
	for (Ball* Ball : Balls)
	{
		Ball->Tick(deltaTime);
	}
}

void GameManager::Terminate()
{
	// End of game logic if needed
}

void GameManager::CollisionCheck()
{
	for (int i = 0; i < NUM_BALLS; i++)
	{
		// Collision detection.
		for (int j = 0; j < NUM_BALLS; j++) 
		{
			Ball* EntityA = Balls[i];
			Ball* EntityB = Balls[j];
			if (EntityA != EntityB) {
				float limitSquared = (Balls[i]->GetRadius() + Balls[j]->GetRadius()) * (Balls[i]->GetRadius() + Balls[j]->GetRadius());
				if (vlen2(Balls[i]->GetPosition() - Balls[j]->GetPosition()) <= limitSquared) 
				{
					EntityA->OnCollide();
					EntityB->OnCollide();
					break;
				}
			}
		}
	}
}

void GameManager::Initialize()
{
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) 
	{
		Balls[i]->SetPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		Balls[i]->SetVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
		Balls[i]->SetRadius(16.f);
		Balls[i]->SetSprite(texsmallball);
	}
}
