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
	for (Entity* entity : world->GetEntities())
	{
		CollisionComponent* otherComponent = entity->GetComponent<CollisionComponent>();
		if (otherComponent && this != otherComponent)
		{
			float limitSquared = (this->GetRadius() + otherComponent->GetRadius()) * (this->GetRadius() + otherComponent->GetRadius());
			if (vlen2(position - otherComponent->GetPosition()) <= limitSquared)
			{
				CollisionMessage message = CollisionMessage(otherComponent);
				owner->BroadcastMessage(&message);
				otherComponent->owner->BroadcastMessage(&message);
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
