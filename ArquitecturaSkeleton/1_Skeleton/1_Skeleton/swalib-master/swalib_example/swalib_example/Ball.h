#pragma once
#include "Entity.h"

class Ball : Entity
{
public:
	Ball();
	~Ball();

	void Tick(float deltaTime);
	void OnCollide();


private:
	vec2   _pos;	// Position.
	vec2   _vel;	// Velocity.
	GLuint _gfx;	// OpenGL for id. for visualization purposes. 
	float  _radius;	// Radius.
	const float MAX_BALL_SPEED = 8.f;	// Max vel. of ball. (pixels/?).

public: 
	vec2 GetPosition() { return _pos; }
	void SetPosition(vec2 pos) { _pos = pos; }

	vec2 GetVelocity() { return _vel; }
	void SetVelocity(vec2 velocity) { _vel = velocity; }

	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }
};


