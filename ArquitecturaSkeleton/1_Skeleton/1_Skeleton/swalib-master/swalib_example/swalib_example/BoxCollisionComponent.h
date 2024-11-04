#pragma once
#include "CollisionComponent.h"

class BoxCollisionComponent : public CollisionComponent
{
public: 
	BoxCollisionComponent(vec2 halfExtents);
	BoxCollisionComponent(BoxCollisionComponent& copy);
	virtual ~BoxCollisionComponent() override;

	virtual bool CircleBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) override;
	virtual bool BoxBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) override;

private:
	vec2 halfExtents;

public:
	vec2 GetHalfExtents() { return halfExtents; }
	void SetHalfExtents(vec2 newExtents) { halfExtents = newExtents; }

	virtual Component* Clone() override;
};

