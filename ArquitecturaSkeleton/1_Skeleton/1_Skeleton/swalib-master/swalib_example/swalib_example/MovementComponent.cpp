#include "MovementComponent.h"
#include "MovementMessage.h"
#include "CollisionMessage.h"
#include "Entity.h"

MovementComponent::MovementComponent()
{
	
}

void MovementComponent::Tick(float deltaTime)
{
	vec2 newPosition = position + velocity * deltaTime;
	position = newPosition;
	previousMovement = velocity * deltaTime;

	//Messages
	MovementMessage message = MovementMessage(position);
	owner->BroadcastMessage(&message);
	owner->SetPosition(position);
}


void MovementComponent::ReceiveMessage(Message* message)
{
	// Guard clause
	CollisionMessage* collisionMessage = dynamic_cast<CollisionMessage*>(message);
	if (!collisionMessage)
	{
		return;
	}

	if (collisionMessage)
	{
		// Negate previous movement, velocity is handled on a case by case basis
		position -= previousMovement;
	}

	/*if (collisionMessage->collisionType == CollisionType::ComponentCollision)
	{
		velocity *= -1.0f;
		position -= previousMovement; 
	}
	else if (collisionMessage->collisionType == CollisionType::ScreenEdgeCollision)
	{
		if (collisionMessage->collisionDirection == CollisionDirection::Horizontal)
		{
			velocity.x *= -1.0f;
		}
		else if (collisionMessage->collisionDirection == CollisionDirection::Vertical)
		{
			velocity.y *= -1.0f;
		}
		position -= previousMovement;
	}*/
}
