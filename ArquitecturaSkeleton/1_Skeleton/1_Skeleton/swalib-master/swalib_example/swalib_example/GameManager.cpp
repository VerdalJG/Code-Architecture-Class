#include "GameManager.h"
#include "Ball.h"
#include "Timer.h"
#include "World.h"
#include "Sprite.h"


GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

void GameManager::Slot()
{
	timer->UpdateTime();
	while (timer->ShouldTick())
	{
		world->Tick(timer->GetFixedTickRate());
		CollisionCheck();
	}
}

void GameManager::Tick(float deltaTime)
{
	
}

void GameManager::Terminate()
{
	if (world)
	{
		for (Entity* entity : world->GetEntities())
		{
			delete(entity);
		}
		delete(world);
	}
}

void GameManager::CollisionCheck()
{
	for (uint i = 0; i < NUM_BALLS; i++)
	{
		// Collision detection.
		for (uint j = 0; j < NUM_BALLS; j++) 
		{
			Ball* ballA = static_cast<Ball*>(world->GetEntities()[i]);
			Ball* ballB = static_cast<Ball*>(world->GetEntities()[j]);
			if (ballA != ballB) 
			{
				float LimitSquared = (ballA->GetRadius() + ballB->GetRadius()) * (ballA->GetRadius() + ballB->GetRadius());
				if (vlen2(ballA->GetPosition() - ballB->GetPosition()) <= LimitSquared)
				{
					ballA->OnCollide();
					ballB->OnCollide();
					break;
				}
			}
		}
	}
}


void GameManager::Initialize(TimeManager* _Timer)
{
	// Init game state.
	world = new World();
	timer = _Timer;

	for (int i = 0; i < NUM_BALLS; i++)
	{
		world->AddEntity(new Ball());
	}
}
