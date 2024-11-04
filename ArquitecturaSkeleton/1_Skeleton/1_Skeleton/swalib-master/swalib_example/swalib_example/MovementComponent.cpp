#include "MovementComponent.h"
#include "MovementMessage.h"
#include "CollisionMessage.h"
#include "Entity.h"
#include "World.h"


MovementComponent::MovementComponent()
{
	
}

MovementComponent::MovementComponent(const MovementComponent& copy) :
	worldPosition(copy.worldPosition),
	previousMovement(copy.previousMovement),
	velocity(copy.velocity),
	gravity(copy.gravity)
{
}

void MovementComponent::Tick(float deltaTime)
{
	if (gravity)
	{
		velocity.y -= GetWorld()->GRAVITY_SCALE;
	}
	vec2 newPosition = worldPosition + velocity * deltaTime;
	worldPosition = newPosition;
	previousMovement = velocity * deltaTime;

	//Messages
	owner->SetWorldPosition(worldPosition);
}


void MovementComponent::ReceiveMessage(Message* message)
{
	CollisionMessage* collisionMessage = dynamic_cast<CollisionMessage*>(message);
	if (collisionMessage)
	{
		// Negate previous movement, velocity is handled on a case by case basis
		vec2 collisionNormal = collisionMessage->normal;
		worldPosition += collisionNormal * collisionMessage->depth;
		float dotProduct = velocity.x * collisionNormal.x + velocity.y * collisionNormal.y;
		vec2 reflectedVelocity = velocity - 2 * dotProduct * collisionNormal;
		velocity = reflectedVelocity; // This assumes no loss of energy
	}

	MovementMessage* movementMessage = dynamic_cast<MovementMessage*>(message);
	if (movementMessage)
	{
		worldPosition = movementMessage->newPosition;
	}
}

Component* MovementComponent::Clone()
{
	MovementComponent* clone = new MovementComponent(*this); // Use copy constructor
	return clone;
}
