#include "Ball.h"
#include "Globals.h"
#include "World.h"
#include "Sprite.h"
#include "CollisionComponent.h"
#include "CircleCollisionComponent.h"
#include "MovementComponent.h"

Ball::Ball()
{
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

void Ball::OnCollide(Entity* otherEntity)
{
	if (otherEntity->GetComponent<CollisionComponent>()->GetCollisionLayer() == CollisionLayer::Bullet)
	{
		Split();
	}
}

void Ball::Split()
{
	World* world = GetWorld();
	if (!world)
	{
		return;
	}

	if (splitCounter > 0)
	{
		Ball* newBall1 = world->SpawnActor<Ball>(this, GetWorldPosition(), GetWorldScale(), "RedBall1");
		Ball* newBall2 = world->SpawnActor<Ball>(this, GetWorldPosition(), GetWorldScale(), "RedBall2");

		int newSplitCounter = splitCounter - 1;
		newBall1->splitCounter = newSplitCounter;
		newBall2->splitCounter = newSplitCounter;

		float newScale = MAX_SIZE_SCALE - ((MAX_SPLITS - newBall1->splitCounter) * 0.5f);
		newBall1->SetWorldScale(vec2(newScale));
		newBall2->SetWorldScale(vec2(newScale));

		float radius = newBall1->GetComponent<CircleCollisionComponent>()->GetScaledRadius();

		vec2 spawnPosition = GetWorldPosition();
		newBall1->SetWorldPosition(vec2(spawnPosition.x + radius, spawnPosition.y));
		newBall2->SetWorldPosition(vec2(spawnPosition.x - radius, spawnPosition.y));
		newBall1->GetComponent<MovementComponent>()->SetVelocity(VELOCITY_ON_SPLIT);
		newBall2->GetComponent<MovementComponent>()->SetVelocity(VELOCITY_ON_SPLIT * vec2(-1.0f, 1.0f));
	}
	else
	{

	}
	Destroy();
}


