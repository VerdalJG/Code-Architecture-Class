#include "GameManager.h"
#include "Ball.h"
#include "Timer.h"
#include "World.h"
#include "Sprite.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "Render.h"
#include "Entity.h"
#include "WorldManager.h"

#include <include/rapidjson/rapidjson.h>
#include <include/rapidjson/document.h>
#include <include/rapidjson/writer.h>
#include <include/rapidjson/filereadstream.h>
#include <include/rapidjson/stringbuffer.h>
#include <iostream>
#include <cctype>
using namespace rapidjson;


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
		Tick(timer->GetFixedTickRate());
	}
}

void GameManager::Tick(float deltaTime)
{
	World* currentWorld = WorldManager::GetInstance().GetCurrentWorld();
	currentWorld->Tick(timer->GetFixedTickRate());
}

void GameManager::Terminate()
{
	
}


void GameManager::Initialize(TimeManager* _timer)
{
	// Init game state.
	WorldManager::GetInstance().LoadWorld(0);
	timer = _timer;

	//FILE* file = fopen(jsonFilePath, "rb");
	//char* readBuffer = new char[65536]; // use heap
	//FileReadStream stream(file, readBuffer, sizeof(readBuffer));
	//Document document;
	//document.ParseStream(stream);
	//
	//vec2 maxPosition = vec2(document["position"].FindMember("x")->value.GetFloat(), document["position"].FindMember("y")->value.GetFloat());
	//float maxVelocity = document["velocity"].GetFloat();
	//float radius = document["radius"].GetFloat();
	//const char* spriteFilePath = document["RenderComponent"].FindMember("texture")->value.GetString();
	//bool wrapping = document["RenderComponent"].FindMember("wrapping")->value.GetBool();

	//fclose(file);
	//delete[] readBuffer;

	//for (unsigned int i = 0; i < NUM_BALLS; i++)
	//{
	//	Entity* ball = new Ball();

	//	// Set initial movement values
	//	MovementComponent* movementComponent = new MovementComponent();
	//	vec2 intialPosition = vec2(CORE_FRand(0.0f + radius, maxPosition.x - radius), CORE_FRand(0.0f + radius, maxPosition.y - radius));
	//	vec2 initialVelocity = vec2(CORE_FRand(-maxVelocity, maxVelocity), CORE_FRand(-maxVelocity, maxVelocity));
	//	movementComponent->SetPosition(intialPosition);
	//	movementComponent->SetVelocity(initialVelocity);

	//	// Set initial collision values
	//	CollisionComponent* collisionComponent = new CollisionComponent();
	//	collisionComponent->SetRadius(radius);

	//	// Set initial render component values
	//	RenderComponent* renderComponent = new RenderComponent();
	//	vec2 spriteSize = vec2(radius * 2.0f, radius * 2.0f);
	//	Sprite* sprite = new Sprite(spriteFilePath, wrapping, spriteSize);
	//	renderComponent->SetSprite(sprite);

	//	ball->AddComponent(movementComponent);
	//	ball->AddComponent(collisionComponent);
	//	ball->AddComponent(renderComponent);
	//	world->AddEntity(ball);

	//	// Order of execution

	//}
}
