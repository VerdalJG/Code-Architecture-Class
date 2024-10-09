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
	vec2 maxPosition = vec2(document["position"].FindMember("x")->value.GetFloat(), document["position"].FindMember("y")->value.GetFloat());
	float maxVelocity = document["velocity"].GetFloat();
	float radius = document["radius"].GetFloat();
	fclose(fp);

	// Set initial movement values
	MovementComponent* movementComponent = new MovementComponent();
	vec2 intialPosition = vec2(CORE_FRand(0.0 + radius, maxPosition.x - radius), CORE_FRand(0.0 + radius, maxPosition.y - radius));
	vec2 initialVelocity = vec2(CORE_FRand(-maxVelocity, maxVelocity), CORE_FRand(-maxVelocity, maxVelocity));
	movementComponent->SetPosition(intialPosition);
	movementComponent->SetVelocity(initialVelocity);

	// Set initial collision values
	CollisionComponent* collisionComponent = new CollisionComponent();
	collisionComponent->SetRadius(radius);

	RenderComponent* renderComponent = new RenderComponent();
	vec2 spriteSize = vec2(radius * 2.0f, radius * 2.0f);
	//renderComponent->SetGfx(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx")->value.GetString(), false));
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


