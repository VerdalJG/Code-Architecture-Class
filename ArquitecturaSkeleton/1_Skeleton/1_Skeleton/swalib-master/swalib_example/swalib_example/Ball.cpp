#include "Ball.h"
#include "Globals.h"
#include "Render.h"
#include "World.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "Sprite.h"

Ball::Ball()
{
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


