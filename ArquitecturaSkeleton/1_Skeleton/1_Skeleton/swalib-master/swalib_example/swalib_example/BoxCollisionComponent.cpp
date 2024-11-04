#include "BoxCollisionComponent.h"
#include "CircleCollisionComponent.h"
#include "World.h"
#include "Entity.h"
#include "CollisionMessage.h"
#include <algorithm>


BoxCollisionComponent::BoxCollisionComponent(vec2 halfExtents)
{
	this->halfExtents = halfExtents;
	type = ColliderType::Box;
}

BoxCollisionComponent::BoxCollisionComponent(BoxCollisionComponent& copy)
{
	this->halfExtents = copy.GetHalfExtents();
	type = ColliderType::Box;
	SetCollisionLayer(copy.GetCollisionLayer());
}

BoxCollisionComponent::~BoxCollisionComponent()
{
}

bool BoxCollisionComponent::CircleBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection)
{
	CircleCollisionComponent* otherComponent = dynamic_cast<CircleCollisionComponent*>(otherCollider);

	if (!otherComponent)
	{
		return false;
	}

	// Get Position of the circle
	vec2 otherPosition = otherComponent->GetWorldPosition();

	// Get scaled radius
	vec2 otherScale = otherComponent->owner->GetWorldScale();
	float otherRadius = otherComponent->GetRadius() * max(otherScale.x, otherScale.y);

	// Get scaled box
	vec2 worldExtents = halfExtents * owner->GetWorldScale();

	// Calculate the extents of the box (left, right, top, bottom edges)
	float leftEdge = worldPosition.x - worldExtents.x;
	float rightEdge = worldPosition.x + worldExtents.x;
	float topEdge = worldPosition.y + worldExtents.y;
	float bottomEdge = worldPosition.y - worldExtents.y;

	vec2 closestPoint;
	closestPoint.x = max(leftEdge, min(otherPosition.x, rightEdge));
	closestPoint.y = max(bottomEdge, min(otherPosition.y, topEdge));

	// Calculate the vector between the circle's center and this closest point
	vec2 difference = otherPosition - closestPoint;
	float distanceSquared = difference.x * difference.x + difference.y * difference.y;
	float radiusSquared = otherRadius * otherRadius;

	if (distanceSquared > radiusSquared)
	{
		return false;
	}

	float distance = sqrtf(distanceSquared);

	if (distance != 0.0f)
	{
		collisionNormal = difference / distance;
		depthOfIntersection = otherRadius - distance;
	}

	return true;
}

bool BoxCollisionComponent::BoxBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection)
{
	BoxCollisionComponent* otherComponent = dynamic_cast<BoxCollisionComponent*>(otherCollider);
	
	vec2 otherPosition = otherComponent->GetWorldPosition();
	vec2 otherExtents = otherComponent->GetHalfExtents() * otherComponent->owner->GetWorldScale();

	vec2 worldExtents = halfExtents * owner->GetWorldScale();

	// Box 1 edges:
	float b1RightEdge = worldPosition.x + worldExtents.x;
	float b1LeftEdge = worldPosition.x - worldExtents.x;
	float b1TopEdge = worldPosition.y + worldExtents.y;
	float b1BottomEdge = worldPosition.y - worldExtents.y;

	// Box 2 edges:
	float b2RightEdge = otherPosition.x + otherExtents.x;
	float b2LeftEdge = otherPosition.x - otherExtents.x;
	float b2TopEdge = otherPosition.y + otherExtents.y;
	float b2BottomEdge = otherPosition.y - otherExtents.y;

	if (b1RightEdge > b2LeftEdge && b1LeftEdge < b2RightEdge && b1TopEdge > b2BottomEdge && b1BottomEdge < b2TopEdge)
	{
		// Calculate the depth of intersection on both axes
		float depthX = min(b1RightEdge - b2LeftEdge, b2RightEdge - b1LeftEdge);
		float depthY = min(b1TopEdge - b2BottomEdge, b2TopEdge - b1BottomEdge);

		// Determine the axis of least depth of intersection
		if (depthX < depthY) 
		{
			// X-axis collision
			if (worldPosition.x < otherPosition.x) 
			{
				collisionNormal = vec2(-1.0f, 0.0f); // Normal pointing left
			}
			else 
			{
				collisionNormal = vec2(1.0f, 0.0f); // Normal pointing right
			}
			depthOfIntersection = depthX;
		}
		else 
		{
			// Y-axis collision
			if (worldPosition.y < otherPosition.y) 
			{
				collisionNormal = vec2(0.0f, -1.0f); // Normal pointing down
			}
			else 
			{
				collisionNormal = vec2(0.0f, 1.0f); // Normal pointing up
			}
			depthOfIntersection = depthY;
		}
		return true;
	}
	else
	{
		return false;
	}
}

Component* BoxCollisionComponent::Clone()
{
	BoxCollisionComponent* clone = new BoxCollisionComponent(*this); // Use copy constructor
	return clone;
}

//For two rectangles to not be colliding, at least one of these conditions must be true:
//
//  Box 1 is entirely to the left of Box 2 (b1RightEdge < b2LeftEdge)
//	Box 1 is entirely to the right of Box 2 (b1LeftEdge > b2RightEdge)
//	Box 1 is entirely above Box 2 (b1BottomEdge > b2TopEdge)
//	Box 1 is entirely below Box 2 (b1TopEdge < b2BottomEdge)