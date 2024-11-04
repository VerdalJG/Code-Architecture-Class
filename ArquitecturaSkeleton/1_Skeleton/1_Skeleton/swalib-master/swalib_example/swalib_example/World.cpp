#include "World.h"
#include "TimerManager.h"
#include "Sprite.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Background.h"
#include "Widget.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Actor.h"
#include "Solid.h"
#include "Player.h"
#include "GameManager.h"


World::World()
{
	background = new Background();
}

void World::BeginPlay()
{
	InitializeCollisionMatrix();

	for (Actor* actor : actorsToAdd)
	{
		actors.push_back(actor);
	}
	actorsToAdd.clear();

	for (Actor* actor : actors)
	{
		actor->BeginPlay();
	}
}

void World::InitializeCollisionMatrix()
{
	for (int i = 0; i < static_cast<int>(CollisionLayer::NumLayers); ++i) 
	{
		for (int j = 0; j < static_cast<int>(CollisionLayer::NumLayers); ++j) 
		{
			collisionMatrix[i][j] = false; // Default to no collision
		}
	}

	// Define specific layer interactions
	collisionMatrix[static_cast<int>(CollisionLayer::Default)][static_cast<int>(CollisionLayer::Default)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Default)][static_cast<int>(CollisionLayer::Player)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Default)][static_cast<int>(CollisionLayer::Environment)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Default)][static_cast<int>(CollisionLayer::Bullet)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Default)][static_cast<int>(CollisionLayer::Balls)] = true;

	collisionMatrix[static_cast<int>(CollisionLayer::Player)][static_cast<int>(CollisionLayer::Balls)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Player)][static_cast<int>(CollisionLayer::Environment)] = true;

	collisionMatrix[static_cast<int>(CollisionLayer::Balls)][static_cast<int>(CollisionLayer::Player)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Balls)][static_cast<int>(CollisionLayer::Environment)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Balls)][static_cast<int>(CollisionLayer::Bullet)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Balls)][static_cast<int>(CollisionLayer::Balls)] = true;

	collisionMatrix[static_cast<int>(CollisionLayer::Environment)][static_cast<int>(CollisionLayer::Player)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Environment)][static_cast<int>(CollisionLayer::Balls)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Environment)][static_cast<int>(CollisionLayer::Bullet)] = true;

	collisionMatrix[static_cast<int>(CollisionLayer::Bullet)][static_cast<int>(CollisionLayer::Balls)] = true;
	collisionMatrix[static_cast<int>(CollisionLayer::Bullet)][static_cast<int>(CollisionLayer::Environment)] = true;
}

// Check if two layers should collide
bool World::ShouldCollide(CollisionLayer layer1, CollisionLayer layer2) 
{
	return collisionMatrix[static_cast<int>(layer1)][static_cast<int>(layer2)];
}

void World::Terminate()
{
	if (background)
	{
		delete(background);
	}
	for (Actor* actor : actors)
	{
		actor->Destroy();
	}
	for (Solid* solid : solids)
	{
		solid->Destroy();
	}
	actors.clear();
	solids.clear();
	entities.clear();

	UIManager::GetInstance().ResetUI();
}

void World::RegisterActor(Actor* actor)
{
	if (actor)
	{
		actorsToAdd.push_back(actor);
		entities.push_back(actor);
		RenderManager::GetInstance().RegisterEntity(actor);
	}
}

void World::RemoveActor(Actor* actor)
{
	if (actor)
	{
		actors.erase(std::remove(actors.begin(), actors.end(), actor), actors.end());
		entities.erase(std::remove(entities.begin(), entities.end(), actor), entities.end());
		RenderManager::GetInstance().RemoveEntity(actor);
		delete(actor);
	}
}

void World::RegisterSolid(Solid* solid)
{
	if (solid)
	{
		solids.push_back(solid);
		entities.push_back(solid);
		RenderManager::GetInstance().RegisterEntity(solid);
	}
}

void World::RemoveSolid(Solid* solid)
{
	if (solid)
	{
		solids.erase(std::remove(solids.begin(), solids.end(), solid), solids.end());
		entities.erase(std::remove(entities.begin(), entities.end(), solid), entities.end());
		RenderManager::GetInstance().RemoveEntity(solid);
		delete(solid);
	}
}

void World::AddWidget(Widget* widget)
{
	if (widget)
	{
		UIManager::GetInstance().AddWidget(widget);
	}
}

void World::RemoveWidget(Widget* widget)
{
	if (widget)
	{
		UIManager::GetInstance().RemoveWidget(widget);
	}
}

void World::Tick(float deltaTime)
{
	for (Actor* newActor : actorsToAdd)
	{
		actors.push_back(newActor);
	}

	actorsToAdd.clear();

	for (Actor* actor : actors)
	{
		if (actor)
		{
			actor->Tick(deltaTime);
			if (actor->ShouldDestroy())
			{
				RemoveActor(actor);
			}
		}
	}
}

void World::ProcessInputs()
{
	// Get the input manager instance
	InputManager& inputManager = InputManager::GetInstance();

	if (inputManager.ShouldClose())
	{
		GameManager::GetInstance().ExitGame();
		return;
	}

	// Phase 1: Handle UI input
	if (UIManager::GetInstance().IsActive())  // Only if UI is active
	{
		if (inputManager.UIMovingUp())
		{
			UIManager::GetInstance().NavigateUp();
		}
		else if (inputManager.UIMovingDown())
		{
			UIManager::GetInstance().NavigateDown();
		}
		else if (inputManager.IsConfirming())
		{
			UIManager::GetInstance().Confirm();
		}
		// Return early to prevent processing game input while UI is active.
		return;
	}

	// Phase 2: Handle Game input (if UI didn't process the input)

	if (!player)
	{
		return;
	}
	// Movement
	if (inputManager.IsUpPressed()) 
	{
		SetLastDirection(MoveDirection::Up);
	}
	else if (inputManager.IsDownPressed())
	{
		SetLastDirection(MoveDirection::Down);
	}
	else if (inputManager.IsLeftPressed())
	{
		SetLastDirection(MoveDirection::Left);
	}
	else if (inputManager.IsRightPressed())
	{
		SetLastDirection(MoveDirection::Right);
	}

	if (inputManager.IsMovingUp() && GetLastDirection() == MoveDirection::Up)
	{
		player->Move(vec2(0.0f,1.0f));
	}
	else if (inputManager.IsMovingDown() && GetLastDirection() == MoveDirection::Down)
	{
		player->Move(vec2(0.0f, -1.0f));
	}
	else if (inputManager.IsMovingLeft() && GetLastDirection() == MoveDirection::Left)
	{
		player->Move(vec2(-1.0f, 0.0f));
	}
	else if (inputManager.IsMovingRight() && GetLastDirection() == MoveDirection::Right)
	{
		player->Move(vec2(1.0f, 0.0f));
	}
	else
	{
		SetLastDirection(MoveDirection::None);
		player->Move(vec2());
	}

	// Shooting
	if (inputManager.IsShooting())
	{
		player->ShootHarpoon();
	}
}

void World::SetBackground(Background* newBackground)
{
	if (background)
	{
		delete(background);
	}
	background = newBackground;
}
