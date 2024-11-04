#pragma once
#include "Globals.h"
#include "Actor.h"

class MovementComponent;
class Harpoon;
class BoxCollisionComponent;
class RenderComponent;

class Player : public Actor
{
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnCollide(Entity* other);
	virtual void OnTrigger(Entity* other);
	void Move(vec2 direction);
	void ShootHarpoon();

private:
	Harpoon* harpoon = nullptr;
	MovementComponent* movementComponent = nullptr;
	BoxCollisionComponent* collisionComponent = nullptr;
	RenderComponent* renderComponent = nullptr;
	const float acceleration = 40.0f;
	const float climbingSpeed = 80.0f;
	const float maxWalkingVelocity = 100.0f;
	const float maxFallSpeed = 100.0f;
	bool isShooting = false;
	bool isClimbing = false;
	bool canClimb = true;
	bool isGrounded = true;
};

