#include "Ball.h"
#include "Globals.h"
#include "Render.h"
#include "World.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "Sprite.h"

Ball::Ball(const char* jsonFilePath)
{
	FILE* fp = fopen(jsonFilePath, "rb");
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document document;
	document.ParseStream(is);
	fclose(fp);
	vec2 maxPos = vec2(document["pos"].FindMember("x")->value.GetFloat(), document["pos"].FindMember("y")->value.GetFloat());
	float maxVel = document["vel"].GetFloat();
	float radius = document["radius"].GetFloat();
	//vec2 pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
	//vec2 vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
	vec2 pos = vec2(CORE_FRand(0.0, maxPos.x), CORE_FRand(0.0, maxPos.y));
	vec2 vel = vec2(CORE_FRand(-maxVel, +maxVel), CORE_FRand(-maxVel, +maxVel));


	// Set initial movement values
	MovementComponent* movementComponent = new MovementComponent();
	vec2 intialPosition = vec2(CORE_FRand(0.0 + radius, SCR_WIDTH - radius), CORE_FRand(0.0 + radius, SCR_HEIGHT - radius));
	vec2 initialVelocity = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
	movementComponent->SetPosition(intialPosition);
	movementComponent->SetVelocity(initialVelocity);

	// Set initial collision values
	CollisionComponent* collisionComponent = new CollisionComponent();
	collisionComponent->SetRadius(radius);

	RenderComponent* renderComponent = new RenderComponent();
	vec2 spriteSize = vec2(radius * 2.0f, radius * 2.0f);
	renderComponent->SetSprite(new Sprite(RenderEngine::GetInstance().ballTexture, spriteSize));

	// Order of execution
	AddComponent(movementComponent);
	AddComponent(collisionComponent);
	AddComponent(renderComponent);
}

Ball::~Ball()
{
	
}

void Ball::Tick(const float deltaTime)
{
	for (Component* component : components)
	{
		component->Tick(deltaTime);
	}
}


