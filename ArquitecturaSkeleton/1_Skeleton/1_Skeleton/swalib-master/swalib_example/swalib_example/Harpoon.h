#pragma once
#include "Actor.h"
class RenderComponent;
class MovementComponent;
class BoxCollisionComponent;
class HarpoonBody;

class Harpoon : public Actor
{
public:
	Harpoon();
	virtual ~Harpoon() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnCollide(Entity* other) override;

	void ResetHarpoon();
	bool IsOnScreen();
	void Fire(vec2 firePosition);

	

private:
	HarpoonBody* bodyEntity = nullptr;
	BoxCollisionComponent* collisionComponent = nullptr;
	MovementComponent* movementComponent = nullptr;
	const float bulletSpeed = 150.0f;
	float floorHeight = 0;

public:
	void SetBodyEntity(HarpoonBody* newBodyEntity) { bodyEntity = newBodyEntity; }
};

