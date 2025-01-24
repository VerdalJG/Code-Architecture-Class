#include "Globals.h"

#include "WorldManager.h"
#include "GameManager.h"
#include "UIManager.h"
#include "RenderManager.h"
#include "Animation.h"

#include "TextWidget.h"
#include "ImageWidget.h"
#include "CursorWidget.h"
#include "ButtonWidget.h"

#include "World.h"
#include "Wall.h"
#include "Background.h"
#include "Sprite.h"
#include "Player.h"
#include "Harpoon.h"
#include "HarpoonBody.h"
#include "Ball.h"

#include "CircleCollisionComponent.h"
#include "BoxCollisionComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"


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
	Sprite* backgroundSprite = RenderManager::GetInstance().LoadSprite("Level1Background", "data/BGLevel1.png", false);
	world->GetBackground()->SetSprite(backgroundSprite);
	CreateBorders(world);
	CreateHarpoon(world);
	CreatePlayer(world);
	CreateBalls(world);
	CreateGameUI(world);


	UIManager::GetInstance().SetActive(false);

	currentWorld = world;
	currentWorld->BeginPlay();
}

void WorldManager::UnloadCurrentWorld()
{
	if (currentWorld)
	{
		currentWorld->PrepareForTermination();
	}
}

void WorldManager::CreateBorders(World* world)
{
	if (!world) 
	{
		return;
	}
	// Load Sprites
	Sprite* brickHSprite = RenderManager::GetInstance().LoadSprite("BrickH", "data/brickH.png", true);
	Sprite* brickVSprite = RenderManager::GetInstance().LoadSprite("BrickV", "data/brickV.png", true);

	// Calculate scales
	vec2 horizontalWallScale = vec2(SCR_WIDTH / brickHSprite->GetSize().x, 1.0f);
	vec2 verticalWallScale = vec2(1.0f, SCR_HEIGHT / brickVSprite->GetSize().y);

	// Calculate positions
	vec2 bottomWallPosition = vec2(SCR_WIDTH / 2, brickHSprite->GetSize().y / 2);
	vec2 topWallPosition = vec2(SCR_WIDTH / 2, SCR_HEIGHT - brickHSprite->GetSize().y / 2);
	vec2 leftWallPosition = vec2(brickVSprite->GetSize().x / 2, SCR_HEIGHT / 2);
	vec2 rightWallPosition = vec2(SCR_WIDTH - brickVSprite->GetSize().x / 2, SCR_HEIGHT / 2);

	vec2 horizontalWallExtents = vec2(brickHSprite->GetSize().x / 2, brickHSprite->GetSize().y / 2);
	vec2 verticalWallExtents = vec2(brickVSprite->GetSize().x / 2, brickVSprite->GetSize().y / 2);

	// Create borders
	Wall* bottomWall = CreateWall("BottomWall", horizontalWallScale, bottomWallPosition, brickHSprite, world);
	Wall* topWall = CreateWall("TopWall", horizontalWallScale, topWallPosition, brickHSprite, world);
	Wall* leftWall = CreateWall("LeftWall", verticalWallScale, leftWallPosition, brickVSprite, world);
	Wall* rightWall = CreateWall("RightWall", verticalWallScale, rightWallPosition, brickVSprite, world);

	// Add in order of rendering
	world->RegisterSolid(leftWall);
	world->RegisterSolid(rightWall);
	world->RegisterSolid(bottomWall);
	world->RegisterSolid(topWall);
}

void WorldManager::CreatePlayer(World* world)
{
	if (!world)
	{
		return;
	}
	Player* player = new Player();

	// Setup movement component
	MovementComponent* movementComponent = new MovementComponent();
	movementComponent->SetWorldPosition(vec2(320, 33)); // TODO: Load from jsonfile


	// Setup render component
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->SetRenderMode(RenderMode::Scaled);

	// Setup Animations
	Animation* playerWalkAnimation = new Animation("Walking", AnimationMode::Individual);
	Sprite* playerWalk0 = RenderManager::GetInstance().LoadSprite("PlayerWalk0", "data/Player/PlayerWalk0.png", false);
	Sprite* playerWalk1 = RenderManager::GetInstance().LoadSprite("PlayerWalk1", "data/Player/PlayerWalk1.png", false);
	Sprite* playerWalk2 = RenderManager::GetInstance().LoadSprite("PlayerWalk2", "data/Player/PlayerWalk2.png", false);
	playerWalkAnimation->AddFrame(playerWalk0);
	playerWalkAnimation->AddFrame(playerWalk1);
	playerWalkAnimation->AddFrame(playerWalk2);
	playerWalkAnimation->AddFrame(playerWalk1); // for looping

	Animation* playerShootAnimation = new Animation("Shooting", AnimationMode::Individual, false);
	Sprite* playerShoot0 = RenderManager::GetInstance().LoadSprite("PlayerShoot0", "data/Player/PlayerShoot0.png", false);
	Sprite* playerShoot1 = RenderManager::GetInstance().LoadSprite("PlayerShoot1", "data/Player/PlayerShoot1.png", false);
	playerShootAnimation->AddFrame(playerShoot0);
	playerShootAnimation->AddFrame(playerShoot1);

	Animation* playerClimbAnimation = new Animation("Climbing", AnimationMode::Individual);
	Sprite* playerClimb0 = RenderManager::GetInstance().LoadSprite("PlayerClimb0", "data/Player/PlayerClimb0.png", false);
	Sprite* playerClimb1 = RenderManager::GetInstance().LoadSprite("PlayerClimb1", "data/Player/PlayerClimb1.png", false);
	Sprite* playerClimb2 = RenderManager::GetInstance().LoadSprite("PlayerClimb2", "data/Player/PlayerClimb2.png", false);
	playerClimbAnimation->AddFrame(playerClimb0);
	playerClimbAnimation->AddFrame(playerClimb1);
	playerClimbAnimation->AddFrame(playerClimb2);
	playerClimbAnimation->AddFrame(playerClimb1);

	Animation* playerIdleAnimation = new Animation("Idle", AnimationMode::Individual);
	Sprite* playerStand = RenderManager::GetInstance().LoadSprite("PlayerStand", "data/Player/PlayerStand.png", false);
	playerIdleAnimation->AddFrame(playerStand);

	renderComponent->AddAnimation(playerWalkAnimation);
	renderComponent->AddAnimation(playerShootAnimation);
	renderComponent->AddAnimation(playerClimbAnimation);
	renderComponent->AddAnimation(playerIdleAnimation);
	renderComponent->SetSprite(playerStand);


	// Setup collision component
	BoxCollisionComponent* boxCollisionComponent = new BoxCollisionComponent(playerStand->GetSize() / 2);
	boxCollisionComponent->SetCollisionLayer(CollisionLayer::Player);

	player->AddComponent(movementComponent);
	player->AddComponent(boxCollisionComponent);
	player->AddComponent(renderComponent);

	world->RegisterActor(player);
	world->SetPlayer(player);
}

void WorldManager::CreateHarpoon(World* world)
{
	if (!world)
	{
		return;
	}
	// Setup Harpoon Head
	Harpoon* harpoon = new Harpoon();

	// Setup movement component
	MovementComponent* headMovementComponent = new MovementComponent();
	headMovementComponent->SetWorldPosition(vec2(800, 800)); // Offscreen until we shoot
	headMovementComponent->SetVelocity(vec2(0, 0));

	// Setup render component for head
	RenderComponent* headRenderComponent = new RenderComponent();
	Sprite* headSprite = RenderManager::GetInstance().LoadSprite("HarpoonHead", "data/BulletHead.png", false);
	headRenderComponent->SetSprite(headSprite);
	headRenderComponent->SetRenderMode(RenderMode::Scaled);

	// Setup collision component
	vec2 headHalfExtents = vec2(headSprite->GetSize().x / 2, headSprite->GetSize().y / 2);
	BoxCollisionComponent* headBoxCollisionComponent = new BoxCollisionComponent(headHalfExtents);
	headBoxCollisionComponent->SetCollisionLayer(CollisionLayer::Bullet);

	harpoon->SetName("Harpoon");
	harpoon->AddComponent(headMovementComponent);
	harpoon->AddComponent(headBoxCollisionComponent);
	harpoon->AddComponent(headRenderComponent);


	// Setup Harpoon Body
	HarpoonBody* body = new HarpoonBody();

	// Setup movement component
	MovementComponent* bodyMovementComponent = new MovementComponent();
	bodyMovementComponent->SetWorldPosition(vec2(800, 800)); // Offscreen until we shoot
	bodyMovementComponent->SetVelocity(vec2(0, 0));


	// Setup render component for body
	RenderComponent* bodyRenderComponent = new RenderComponent();
	Sprite* bodySprite = RenderManager::GetInstance().LoadSprite("HarpoonBody", "data/BulletBody.png", true);
	bodyRenderComponent->SetSprite(bodySprite);
	bodyRenderComponent->SetRenderMode(RenderMode::Tiled);

	// Setup collision component
	vec2 bodyHalfExtents = vec2(bodySprite->GetSize().x / 2, bodySprite->GetSize().y / 2);
	BoxCollisionComponent* bodyBoxCollisionComponent = new BoxCollisionComponent(bodyHalfExtents);
	bodyBoxCollisionComponent->SetCollisionLayer(CollisionLayer::Bullet);

	body->SetName("HarpoonBody");
	body->AddComponent(bodyMovementComponent);
	body->AddComponent(bodyBoxCollisionComponent);
	body->AddComponent(bodyRenderComponent);

	harpoon->SetBodyEntity(body);

	world->RegisterActor(harpoon);
	world->RegisterActor(body);
}

void WorldManager::CreateBalls(World* world)
{
	if (!world)
	{
		return;
	}
	Ball* ball = new Ball();

	// Setup movement component
	MovementComponent* movementComponent = new MovementComponent();
	movementComponent->SetWorldPosition(vec2(300, 300));
	movementComponent->SetVelocity(vec2(50, 0));
	movementComponent->SetGravity(true);

	// Setup render component
	RenderComponent* renderComponent = new RenderComponent();
	Sprite* redBallSprite = RenderManager::GetInstance().LoadSprite("RedBall", "data/BallRed.png", false);
	renderComponent->SetSprite(redBallSprite);
	renderComponent->SetRenderMode(RenderMode::Scaled);

	// Setup collision component
	float radius = max(redBallSprite->GetSize().x, redBallSprite->GetSize().y) / 2;
	CircleCollisionComponent* collisionComponent = new CircleCollisionComponent(radius);
	collisionComponent->SetCollisionLayer(CollisionLayer::Balls);
	collisionComponent->SetTrigger(false);

	ball->SetName("BallRedL");
	ball->SetWorldScale(vec2(2.0f));
	ball->SetWorldPosition(vec2(300, 300));
	ball->AddComponent(movementComponent);
	ball->AddComponent(collisionComponent);
	ball->AddComponent(renderComponent);

	world->RegisterActor(ball);
}

Wall* WorldManager::CreateWall(const std::string& name, const vec2& scale, const vec2& worldPosition, Sprite* sprite, World* world)
{
	Wall* wall = new Wall();

	// Setup render component
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->SetSprite(sprite);
	renderComponent->SetRenderMode(RenderMode::Tiled);

	// Set initial collision values
	BoxCollisionComponent* boxCollisionComponent = new BoxCollisionComponent(sprite->GetSize() / 2);
	boxCollisionComponent->SetCollisionLayer(CollisionLayer::Environment);

	wall->SetName(name);
	wall->SetWorldScale(scale);
	wall->SetWorldPosition(worldPosition);

	wall->AddComponent(boxCollisionComponent);
	wall->AddComponent(renderComponent);
	return wall;
}

void WorldManager::CreateGameUI(World* world)
{
	TextWidget* scoreText = new TextWidget();
	scoreText->SetText("SCORE: 0");
	scoreText->SetWorldPosition(vec2(400, 400));
	world->AddWidget(scoreText);
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
	UIManager::GetInstance().ResetUI();
	// Create Main Menu world
	World* world = new World();
	Sprite* backgroundSprite = RenderManager::GetInstance().LoadSprite("MainMenuBG", "data/circle-bkg-128.png", true);
	world->GetBackground()->SetSprite(backgroundSprite);
	world->GetBackground()->SetBackgroundTiledMode(true);

	TextWidget* playText = new TextWidget();
	playText->SetText("PLAY GAME");
	playText->SetWorldPosition(vec2(250, 150));
	world->AddWidget(playText);

	ButtonWidget* playButton = new ButtonWidget();
	playButton->AddListener(std::bind(&WorldManager::LoadWorld, this, WorldType::GameWorld));
	playButton->AttachToWidget(playText);

	TextWidget* exitText = new TextWidget();
	exitText->SetText("EXIT GAME");
	exitText->SetWorldPosition(vec2(250, 100));
	world->AddWidget(exitText);

	ButtonWidget* exitButton = new ButtonWidget();
	exitButton->AddListener(std::bind(&GameManager::ExitGame, GameManager::GetInstance()));
	exitButton->AttachToWidget(exitText);

	CursorWidget* cursor = new CursorWidget();
	Sprite* cursorSprite = RenderManager::GetInstance().LoadSprite("RedBall", "data/BallRed.png", false);
	cursor->SetSprite(cursorSprite);
	cursor->AddSelectableWidget(playText);
	cursor->AddSelectableWidget(exitText);
	cursor->SetScale(vec2(0.5f, 0.5f));
	cursor->SetOffset(vec2(180, 10));
	world->AddWidget(cursor);
	UIManager::GetInstance().SetControllingWidget(cursor);

	ImageWidget* gameTitle = new ImageWidget();
	Sprite* titleSprite = RenderManager::GetInstance().LoadSprite("GameTitle", "data/title.png", false);
	gameTitle->SetSprite(titleSprite);
	vec2 titleScreenScale = vec2(0.7f, 0.7f);
	gameTitle->SetScale(titleScreenScale);
	gameTitle->SetWorldPosition(vec2(320, 350));
	world->AddWidget(gameTitle);

	UIManager::GetInstance().SetActive(true);

	currentWorld = world;
}

World* WorldManager::GetCurrentWorld()
{
	return currentWorld;
}
