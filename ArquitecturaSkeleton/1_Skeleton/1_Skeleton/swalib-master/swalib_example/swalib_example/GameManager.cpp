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
	if (world)
	{
		for (Entity* entity : world->GetEntities())
		{
			delete(entity);
		}
		delete(world);
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
