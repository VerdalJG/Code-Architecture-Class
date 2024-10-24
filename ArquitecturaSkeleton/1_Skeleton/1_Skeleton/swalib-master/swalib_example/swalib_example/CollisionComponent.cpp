#include "CollisionComponent.h"
#include "Entity.h"
#include "World.h"
#include "CollisionMessage.h"
#include "MovementMessage.h"

CollisionComponent::CollisionComponent()
	: radius(16.0f)
{
}

void CollisionComponent::Tick(float deltaTime)
{
	CollisionCheck();
	ScreenLimitCheck();
}

void CollisionComponent::CollisionCheck()
{
	// Collision detection.
	World* world = GetWorld();
	for (Entity* otherEntity : world->GetEntities())
	{
		if (otherEntity == owner)
		{
			continue;
		}

		CollisionComponent* otherComponent = otherEntity->GetComponent<CollisionComponent>();
		if (otherComponent)
		{
			float limitSquared = (this->GetRadius() + otherComponent->GetRadius()) * (this->GetRadius() + otherComponent->GetRadius());
			if (vlen2(position - otherComponent->GetPosition()) <= limitSquared)
			{
				CollisionMessage message = CollisionMessage(otherComponent);
				owner->BroadcastMessage(&message);
				
				// For specific behavior on collision
				owner->OnCollide(otherEntity);
				otherEntity->OnCollide(owner);
			}
		}
	}
}

void CollisionComponent::ScreenLimitCheck()
{
	CollisionMessage message;
	bool collided = false;

	if (position.x + radius > SCR_WIDTH || position.x - radius < 0) 
	{
		message = CollisionMessage(CollisionDirection::Horizontal);
		collided = true;
	}
	if (position.y + radius > SCR_HEIGHT || position.y - radius < 0) 
	{
		message = CollisionMessage(CollisionDirection::Vertical);
		collided = true;
	}

	if (collided)
	{
		owner->BroadcastMessage(&message);
	}
}

void CollisionComponent::ReceiveMessage(Message* message)
{
	MovementMessage* movementMessage = dynamic_cast<MovementMessage*>(message);
	if (movementMessage) 
	{
		position = movementMessage->newPosition;
	}
}
