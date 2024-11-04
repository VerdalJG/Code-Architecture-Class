#include "CollisionMessage.h"

CollisionMessage::CollisionMessage(CollisionComponent* other, vec2 collisionNormal, float depthOfIntersection) :
	collidingComponent(other),
	normal(collisionNormal),
	depth(depthOfIntersection)
{
}