#include "CollisionMessage.h"

CollisionMessage::CollisionMessage() : 
	collidingComponent(nullptr),
	collisionType(CollisionType::None),
	collisionDirection(CollisionDirection::None)
{
}

CollisionMessage::CollisionMessage(CollisionComponent* other) :
	collisionDirection(CollisionDirection::None)
{
	collisionType = CollisionType::ComponentCollision;
	collidingComponent = other;
}

CollisionMessage::CollisionMessage(CollisionDirection direction) :
	collidingComponent(nullptr)
{
	collisionType = CollisionType::ScreenEdgeCollision;
	collisionDirection = direction;
}
