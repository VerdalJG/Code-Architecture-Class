#include "HarpoonBody.h"
#include "MovementComponent.h"
#include "BoxCollisionComponent.h"
#include "Ball.h"
#include "Harpoon.h"
#include "GameManager.h"

HarpoonBody::HarpoonBody()
{
}

HarpoonBody::~HarpoonBody()
{
}

void HarpoonBody::BeginPlay()
{
	movementComponent = GetComponent<MovementComponent>();
	collisionComponent = GetComponent<BoxCollisionComponent>();
}

void HarpoonBody::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
}

void HarpoonBody::OnCollide(Entity* other)
{
	harpoon->ResetHarpoon();

	Ball* ball = dynamic_cast<Ball*>(other);
	if (ball)
	{
		// Add some score here
		GameManager::GetInstance().AddScore();
	}
}

