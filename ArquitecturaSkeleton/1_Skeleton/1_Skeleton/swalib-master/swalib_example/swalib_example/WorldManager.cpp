#include "WorldManager.h"
#include "Background.h"
#include "Sprite.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include "CursorWidget.h"
#include "World.h"

WorldManager& WorldManager::GetInstance()
{
	static WorldManager instance;
	return instance;
}

void WorldManager::Initialize()
{

}

void WorldManager::Terminate()
{
	for (World* world : worlds)
	{
		world->Terminate();
		delete(world);
	}
}

void WorldManager::LoadWorld(int worldIndex)
{
	if (worldIndex < 0)
	{
		return;
	}

	currentWorldIndex = worldIndex;

	if (worldIndex == 0)
	{
		LoadMainMenu();
	}
	else
	{
		LoadLevel(worldIndex);
	}
}

void WorldManager::LoadLevel(int level)
{
	// Level loading logic SOONTM
}

void WorldManager::LoadMainMenu()
{
	// Create Main Menu world
	World* world = new World();
	world->SetWorldType(WorldType::MainMenu);
	world->GetBackground()->SetSprite("data/circle-bkg-128.png", true);

	TextWidget* playText = new TextWidget();
	playText->SetText("PLAY GAME");
	playText->SetSelectability(true);
	playText->SetPosition(vec2(250, 150));
	world->AddWidget(playText);

	TextWidget* exitText = new TextWidget();
	exitText->SetText("EXIT GAME");
	exitText->SetSelectability(true);
	exitText->SetPosition(vec2(250, 100));
	world->AddWidget(exitText);

	CursorWidget* cursor = new CursorWidget();
	Sprite* cursorSprite = new Sprite("data/BallRed.png", false, vec2(48, 40));
	cursor->SetSprite(cursorSprite);
	cursor->AddSelectableWidget(exitText);
	cursor->AddSelectableWidget(playText);
	cursor->SetOffset(vec2(50, 0));
	world->AddWidget(cursor);

	ImageWidget* gameTitle = new ImageWidget();
	Sprite* titleSprite = new Sprite("data/title.png", false, vec2(512, 282));
	gameTitle->SetSprite(titleSprite);
	vec2 titleScreenScale = vec2(0.7f, 0.7f);
	gameTitle->SetScale(titleScreenScale);
	gameTitle->SetPosition(vec2(320, 350));
	world->AddWidget(gameTitle);

	worlds.push_back(world);
}

World* WorldManager::GetCurrentWorld()
{
	if (currentWorldIndex >= 0 && currentWorldIndex < worlds.size())
	{
		return worlds[currentWorldIndex];
	}
	return nullptr;
}
