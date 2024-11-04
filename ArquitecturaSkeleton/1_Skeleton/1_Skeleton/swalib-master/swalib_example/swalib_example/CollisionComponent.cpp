#include "CollisionComponent.h"
#include "Entity.h"
#include "World.h"
#include "CollisionMessage.h"
#include "MovementMessage.h"

CollisionComponent::CollisionComponent() : 
	type(ColliderType::Unknown),
	layer(CollisionLayer::Default)
{
}

void CollisionComponent::Tick(float deltaTime)
{
	// Collision detection.
	World* world = GetWorld();
	for (Entity* otherEntity : world->GetEntities())
	{
		if (otherEntity == owner)
		{
			continue;
		}

		CollisionComponent* otherCollider = otherEntity->GetComponent<CollisionComponent>();

		if (!otherCollider)
		{
			continue;
		}

		CollisionLayer otherLayer = otherCollider->GetCollisionLayer();

		// Only proceed with collision check if the layers are set to collide
		if (world->ShouldCollide(layer, otherLayer)) 
		{
			CollisionCheck(this, otherCollider);
		}
	}
	
}

void CollisionComponent::CollisionCheck(CollisionComponent* ownerComponent, CollisionComponent* otherComponent)
{
	bool collided = false;
	vec2 collisionNormal;
	float depthOfIntersection = 0;

	ColliderType otherType = otherComponent->GetColliderType();
		
	// Both Circles
	if (type == ColliderType::Circle && otherType == ColliderType::Circle)
	{
		collided = CircleCircleCollisionCheck(otherComponent, collisionNormal, depthOfIntersection);
	}
	// Box and Circle
	else if (type == ColliderType::Circle && otherType == ColliderType::Box || type == ColliderType::Box && otherType == ColliderType::Circle)
	{
		collided = CircleBoxCollisionCheck(otherComponent, collisionNormal, depthOfIntersection);
	}
	// Both Boxes
	else if (type == ColliderType::Box && otherType == ColliderType::Box)
	{
		collided = BoxBoxCollisionCheck(otherComponent, collisionNormal, depthOfIntersection);
	}

	if (collided)
	{
		if (isTrigger || otherComponent->IsTrigger())
		{
			owner->OnTrigger(otherComponent->owner);
			otherComponent->owner->OnCollide(owner);
		}
		else
		{
			CollisionMessage message = CollisionMessage(otherComponent, collisionNormal, depthOfIntersection);
			owner->BroadcastMessage(&message);

			// For specific behavior on collision
			owner->OnCollide(otherComponent->owner);
			otherComponent->owner->OnCollide(owner);
		}
	}
	
}

void CollisionComponent::OnAttach()
{
	worldPosition = owner->GetWorldPosition();
}


void CollisionComponent::ReceiveMessage(Message* message)
{
	MovementMessage* movementMessage = dynamic_cast<MovementMessage*>(message);
	if (movementMessage) 
	{
		worldPosition = movementMessage->newPosition;
	}
}
