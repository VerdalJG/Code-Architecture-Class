#pragma once
#include "GameLogic.h"

class Ball
{
public:
	Ball();

	vec2 GetPosition() { return _pos; }
	void SetPosition(vec2 pos) { _pos = pos; }

	vec2 GetVelocity() { return _vel; }
	void SetVelocity(vec2 velocity) { _vel = velocity; }

	GLuint GetSprite() { return _gfx; }
	void SetSprite(GLuint sprite) { _gfx = sprite; }

	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

private:
	vec2   _pos;	// Position.
	vec2   _vel;	// Velocity.
	GLuint _gfx;	// OpenGL for id. for visualization purposes. 
	float  _radius;	// Radius.
};

const unsigned int NUM_BALLS = 10;	// Max. num balls.
Ball balls[NUM_BALLS];	// Array of balls.
const float MAX_BALL_SPEED = 8.f;	// Max vel. of ball. (pixels/?).

// Textures
GLuint texbkg;
GLuint texsmallball;

