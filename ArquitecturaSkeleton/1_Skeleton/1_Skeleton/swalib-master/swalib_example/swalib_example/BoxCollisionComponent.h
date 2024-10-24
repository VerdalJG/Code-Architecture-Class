#pragma once
#include "CollisionComponent.h"

class BoxCollisionComponent : public CollisionComponent
{
public: 
	BoxCollisionComponent();
	virtual ~BoxCollisionComponent() override;

private:
	vec2 halfExtents;

public:
	vec2 GetExtents() { return halfExtents; }
	void SetHalfExtents(vec2 newExtents) { halfExtents = newExtents; }
};

