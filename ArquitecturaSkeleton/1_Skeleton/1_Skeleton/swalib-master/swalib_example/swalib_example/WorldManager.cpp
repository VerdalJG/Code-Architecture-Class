#include "Globals.h"

#include "WorldManager.h"
#include "GameManager.h"
#include "UIManager.h"
#include "RenderManager.h"

#include "TextWidget.h"
#include "ImageWidget.h"
#include "CursorWidget.h"
#include "ButtonWidget.h"

#include "World.h"
#include "Wall.h"
#include "Background.h"
#include "Sprite.h"

#include "BoxCollisionComponent.h"
#include "RenderComponent.h"


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
	UnloadCurrentWorld();
}

void WorldManager::LoadWorld(WorldType worldType)
{
	UnloadCurrentWorld();

	if (worldType == WorldType::MainMenu)
	{
		LoadMainMenu();
	}
	else if (worldType == WorldType::GameWorld)
	{
		LoadGameWorld();
	}
}

void WorldManager::LoadGameWorld()
{
	World* world = new World();
	Sprite* backgroundSprite = RenderEngine::GetInstance().CreateSprite("Level1Background,", "data/BGLevel1.png", false);
	world->GetBackground()->SetSprite(backgroundSprite);
	CreateBorders(world);
	currentWorld = world;
}

void WorldManager::UnloadCurrentWorld()
{
	if (currentWorld)
	{
		currentWorld->Terminate();
		delete(currentWorld);
	}
}

void WorldManager::CreateBorders(World* world)
{
	// Load Sprites
	Sprite* brickHSprite = RenderEngine::GetInstance().CreateSprite("BrickH", "data/brickH.png", true);
	Sprite* brickVSprite = RenderEngine::GetInstance().CreateSprite("BrickV", "data/brickV.png", true);

	// Calculate scales
	vec2 horizontalWallScale = vec2(SCR_WIDTH / brickHSprite->GetSize().x, 1.0f);
	vec2 verticalWallScale = vec2(1.0f, SCR_HEIGHT / brickVSprite->GetSize().y);

	// Calculate positions
	vec2 bottomWallPosition = vec2(SCR_WIDTH / 2, brickHSprite->GetSize().y / 2);
	vec2 topWallPosition = vec2(SCR_WIDTH / 2, SCR_HEIGHT - brickHSprite->GetSize().y / 2);
	vec2 leftWallPosition = vec2(brickVSprite->GetSize().x / 2, SCR_HEIGHT / 2);
	vec2 rightWallPosition = vec2(SCR_WIDTH - brickVSprite->GetSize().x / 2, SCR_HEIGHT / 2);

	// Create borders
	Wall* bottomWall = CreateWall("BottomWall", horizontalWallScale, bottomWallPosition, horizontalWallScale / 2, brickHSprite, world);
	Wall* topWall = CreateWall("TopWall", horizontalWallScale, topWallPosition, horizontalWallScale / 2, brickHSprite, world);
	Wall* leftWall = CreateWall("LeftWall", verticalWallScale, leftWallPosition, verticalWallScale / 2, brickVSprite, world);
	Wall* rightWall = CreateWall("RightWall", verticalWallScale, rightWallPosition, verticalWallScale / 2, brickVSprite, world);

	// Add in order of rendering
	world->AddSolid(leftWall);
	world->AddSolid(rightWall);
	world->AddSolid(bottomWall);
	world->AddSolid(topWall);
}

Wall* WorldManager::CreateWall(const std::string& name, const vec2& scale, const vec2& position, const vec2& halfExtents, Sprite* sprite, World* world)
{
	Wall* wall = new Wall();
	// Setup render component
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->SetSprite(sprite);
	renderComponent->SetRenderMode(RenderMode::Tiled);

	// Set initial collision values
	BoxCollisionComponent* boxCollisionComponent = new BoxCollisionComponent();
	boxCollisionComponent->SetHalfExtents(halfExtents);

	wall->SetName(name);
	wall->SetScale(scale);
	wall->SetPosition(position);

	wall->AddComponent(boxCollisionComponent);
	wall->AddComponent(renderComponent);
	return wall;
}

void WorldManager::LoadLevel(int level)
{
	// Level loading logic
	if (level == 1)
	{
		World* world = new World();
	}
	else if (level == 2)
	{

	}
}

void WorldManager::LoadMainMenu()
{
	// Create Main Menu world
	World* world = new World();
	Sprite* backgroundSprite = RenderEngine::GetInstance().CreateSprite("MainMenuBG", "data/circle-bkg-128.png", true);
	world->GetBackground()->SetSprite(backgroundSprite);
	world->GetBackground()->SetBackgroundTiledMode(true);

	TextWidget* playText = new TextWidget();
	playText->SetText("PLAY GAME");
	playText->SetPosition(vec2(250, 150));
	world->AddWidget(playText);

	ButtonWidget* playButton = new ButtonWidget();
	playButton->AddListener(std::bind(&WorldManager::LoadWorld, this, WorldType::GameWorld));
	playButton->AttachToWidget(playText);

	TextWidget* exitText = new TextWidget();
	exitText->SetText("EXIT GAME");
	exitText->SetPosition(vec2(250, 100));
	world->AddWidget(exitText);

	ButtonWidget* exitButton = new ButtonWidget();
	exitButton->AddListener(std::bind(&GameManager::ExitGame, GameManager::GetInstance()));
	exitButton->AttachToWidget(exitText);

	CursorWidget* cursor = new CursorWidget();
	Sprite* cursorSprite = RenderEngine::GetInstance().CreateSprite("RedBall", "data/BallRed.png", false);
	cursor->SetSprite(cursorSprite);
	cursor->AddSelectableWidget(playText);
	cursor->AddSelectableWidget(exitText);
	cursor->SetScale(vec2(0.5f, 0.5f));
	cursor->SetOffset(vec2(180, 10));
	world->AddWidget(cursor);
	UIManager::GetInstance().SetControllingWidget(cursor);

	ImageWidget* gameTitle = new ImageWidget();
	Sprite* titleSprite = RenderEngine::GetInstance().CreateSprite("GameTitle", "data/title.png", false);
	gameTitle->SetSprite(titleSprite);
	vec2 titleScreenScale = vec2(0.7f, 0.7f);
	gameTitle->SetScale(titleScreenScale);
	gameTitle->SetPosition(vec2(320, 350));
	world->AddWidget(gameTitle);

	UIManager::GetInstance().SetActive(true);

	currentWorld = world;
}

World* WorldManager::GetCurrentWorld()
{
	return currentWorld;
}
