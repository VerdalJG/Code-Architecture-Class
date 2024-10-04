#pragma once
#include "Globals.h"
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	~Ball();

	virtual void Tick(const float DeltaTime) override;
	void RunPhysics(const float deltaTime);
	bool CollisionCheck(vec2 newPosition);
	void OnCollide();


private:
	vec2 velocity;	// Velocity.
	float radius;	// Radius.
	const float MAX_BALL_SPEED = 80.0f;	// Max vel. of ball. (pixels/?).

public:
	vec2 GetVelocity() { return velocity; }
	void SetVelocity(vec2 velocity) { velocity = velocity; }

	float GetRadius() { return radius; }
	void SetRadius(float radius) { radius = radius; }
};


