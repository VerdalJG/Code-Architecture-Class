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
	}
}

void GameManager::Tick(float deltaTime)
{
	
}

void GameManager::Terminate()
{
	// End of game logic if needed
}

void GameManager::CollisionCheck()
{
	for (uint i = 0; i < NUM_BALLS; i++)
	{
		// Collision detection.
		for (uint j = 0; j < NUM_BALLS; j++) 
		{
			Ball* EntityA = Balls[i];
			Ball* EntityB = Balls[j];
			if (EntityA != EntityB) 
			{
				float LimitSquared = (Balls[i]->GetRadius() + Balls[j]->GetRadius()) * (Balls[i]->GetRadius() + Balls[j]->GetRadius());
				if (vlen2(Balls[i]->GetPosition() - Balls[j]->GetPosition()) <= LimitSquared)
				{
					EntityA->OnCollide();
					EntityB->OnCollide();
					break;
				}
			}
		}
	}
}

void GameManager::RegisterEntity(Entity* Entity)
{
	Entities.push_back(Entity);
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
