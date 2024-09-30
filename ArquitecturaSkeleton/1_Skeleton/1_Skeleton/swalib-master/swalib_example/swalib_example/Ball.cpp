#include "Ball.h"

Ball::Ball() :
	_pos(0.0f),
	_vel(0.0f),
	_gfx(0),
	_radius(0.0f)
{}

Ball::~Ball()
{

}

void Ball::Tick(const float deltaTime)
{
	// Run balls
	for (int i = 0; i < NUM_BALLS; i++) 
	{
		// New Pos.
		vec2 newPos = _pos + _vel * deltaTime;

		// Rebound on margins.
		if (_pos.x > SCR_WIDTH || _pos.x < 0) 
		{
			_vel.x *= -1.0;
		}
		if (_pos.y > SCR_HEIGHT || _pos.y < 0)
		{
			_vel.y *= -1.0;
		}
	}
}

void Ball::OnCollide()
{
	// Rebound!
	_vel *= -1.f;
}