#pragma once
#include "Actor.h"

class RenderComponent;
class MovementComponent;
class BoxCollisionComponent;
class Harpoon;

class HarpoonBody : public Actor
{
public:
	HarpoonBody();
	virtual ~HarpoonBody() override;

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void OnCollide(Entity* other);

private:
	Harpoon* harpoon = nullptr;
	BoxCollisionComponent* collisionComponent = nullptr;
	MovementComponent* movementComponent = nullptr;

public:
	BoxCollisionComponent* GetBoxCollider() { return collisionComponent; }
	MovementComponent* GetMovementComponent() { return movementComponent; }
	void SetHarpoon(Harpoon* actor) { harpoon = actor; }
};

