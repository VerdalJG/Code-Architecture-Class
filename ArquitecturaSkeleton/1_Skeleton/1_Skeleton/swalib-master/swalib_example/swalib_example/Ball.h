#pragma once
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	~Ball();

	virtual void Tick(float DeltaTime) override;
	void OnCollide();


private:
	vec2   Velocity;	// Velocity.
	float  Radius;	// Radius.
	const float MAX_BALL_SPEED = 80.0f;	// Max vel. of ball. (pixels/?).

public:
	vec2 GetVelocity() { return Velocity; }
	void SetVelocity(vec2 velocity) { Velocity = velocity; }

	float GetRadius() { return Radius; }
	void SetRadius(float radius) { Radius = radius; }
};


