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


World::World()
{
	background = new Background();
}

void World::Terminate()
{
	if (background)
	{
		delete(background);
	}
	for (Entity* entity : entities)
	{
		delete(entity);
	}

	UIManager::GetInstance().ResetUI();
}

void World::AddActor(Actor* actor)
{
	if (actor)
	{
		actors.push_back(actor);
		entities.push_back(actor);
		RenderEngine::GetInstance().RegisterEntity(actor);
	}
}

void World::RemoveEntity(Actor* actor)
{
	if (actor)
	{
		actors.erase(std::remove(actors.begin(), actors.end(), actor), actors.end());
		entities.erase(std::remove(entities.begin(), entities.end(), actor), entities.end());
		RenderEngine::GetInstance().RemoveEntity(actor);
		delete(actor);
	}
}

void World::AddSolid(Solid* solid)
{
	if (solid)
	{
		solids.push_back(solid);
		entities.push_back(solid);
		RenderEngine::GetInstance().RegisterEntity(solid);
	}
}

void World::RemoveSolid(Solid* solid)
{
	if (solid)
	{
		solids.erase(std::remove(solids.begin(), solids.end(), solid), solids.end());
		entities.erase(std::remove(entities.begin(), entities.end(), solid), entities.end());
		RenderEngine::GetInstance().RemoveEntity(solid);
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
	for (Actor* actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void World::ProcessInputs()
{
	// Get the input manager instance
	InputManager& inputManager = InputManager::GetInstance();

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

	// Movement
	if (inputManager.IsMovingUp())
	{
		player->MoveUp();
	}
	if (inputManager.IsMovingDown())
	{
		player->MoveDown();
	}
	if (inputManager.IsMovingLeft())
	{
		player->MoveLeft();
	}
	if (inputManager.IsMovingRight())
	{
		player->MoveRight();
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
