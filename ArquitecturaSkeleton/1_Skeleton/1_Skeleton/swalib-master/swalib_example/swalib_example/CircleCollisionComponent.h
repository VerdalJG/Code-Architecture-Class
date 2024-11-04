#pragma once
#include "CollisionComponent.h"
#include "Entity.h"

class CircleCollisionComponent : public CollisionComponent
{
public:
	CircleCollisionComponent(float radius);
	CircleCollisionComponent(CircleCollisionComponent& copy);
	virtual ~CircleCollisionComponent() override;

	virtual bool CircleBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) override;
	virtual bool CircleCircleCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) override;

private:
	float radius;

public:
	float GetRadius() { return radius; }
	void SetRadius(float newRadius) { radius = newRadius; }

	float GetScaledRadius() { return radius * max(owner->GetWorldScale().x, owner->GetWorldScale().y); }

	virtual Component* Clone() override;
};

