#include "CircleCollisionComponent.h"
#include "World.h"
#include "Entity.h"
#include "CollisionMessage.h"
#include "BoxCollisionComponent.h"


CircleCollisionComponent::CircleCollisionComponent(float radius)
{
	this->radius = radius;
	type = ColliderType::Circle;
}

CircleCollisionComponent::CircleCollisionComponent(CircleCollisionComponent& copy)
{
	this->radius = copy.GetRadius();
	type = ColliderType::Circle;
	SetCollisionLayer(copy.GetCollisionLayer());
}

CircleCollisionComponent::~CircleCollisionComponent()
{
}

bool CircleCollisionComponent::CircleBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection)
{
	BoxCollisionComponent* otherComponent = dynamic_cast<BoxCollisionComponent*>(otherCollider);
	
	if (!otherComponent)
	{
		return false;
	}

	vec2 otherPosition = otherComponent->GetWorldPosition();
	vec2 otherWorldExtents = otherComponent->GetHalfExtents() * otherComponent->owner->GetWorldScale();
	float scaledRadius = radius * max(owner->GetWorldScale().x, owner->GetWorldScale().y);

	// Calculate the extents of the box (left, right, top, bottom edges)
	float leftEdge = otherPosition.x - otherWorldExtents.x;
	float rightEdge = otherPosition.x + otherWorldExtents.x;
	float topEdge = otherPosition.y + otherWorldExtents.y;
	float bottomEdge = otherPosition.y - otherWorldExtents.y;

	vec2 closestPoint;
	closestPoint.x = max(leftEdge, min(worldPosition.x, rightEdge));
	closestPoint.y = max(bottomEdge, min(worldPosition.y, topEdge));

	// Calculate the vector between the circle's center and this closest point
	vec2 difference = worldPosition - closestPoint;
	float distanceSquared = difference.x * difference.x + difference.y * difference.y;
	float radiusSquared = scaledRadius * scaledRadius;

	if (distanceSquared > radiusSquared)
	{
		return false;
	}

	float distance = sqrtf(distanceSquared);

	if (distance != 0.0f)
	{
		collisionNormal = difference / distance;
		depthOfIntersection = scaledRadius - distance;
	}

	return true;
}

bool CircleCollisionComponent::CircleCircleCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection)
{
	CircleCollisionComponent* otherComponent = dynamic_cast<CircleCollisionComponent*>(otherCollider);
	if (otherComponent)
	{
		vec2 scale = owner->GetWorldScale();
		vec2 otherScale = otherComponent->owner->GetWorldScale();

		float worldRadius = radius * max(scale.x, scale.y);
		float otherWorldRadius = otherComponent->GetRadius() * max(otherScale.x, otherScale.y);

		float combinedRadius = worldRadius + otherWorldRadius;
		float limitSquared = combinedRadius * combinedRadius;

		vec2 delta = otherComponent->GetWorldPosition() - worldPosition;
		float distanceSquared = vlen2(delta);

		if (distanceSquared <= limitSquared)
		{
			collisionNormal = vnorm(delta);
			depthOfIntersection = combinedRadius - sqrt(distanceSquared);
			return true;
		}
	}

	return false;
}

Component* CircleCollisionComponent::Clone()
{
	CircleCollisionComponent* clone = new CircleCollisionComponent(*this); // Use copy constructor
	return clone;
}
