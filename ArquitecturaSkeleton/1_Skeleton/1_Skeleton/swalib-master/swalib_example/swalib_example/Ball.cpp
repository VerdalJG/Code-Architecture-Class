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

void Ball::Slot(const float deltaTime)
{
	// Run balls
	for (int i = 0; i < NUM_BALLS; i++) 
	{
		// New Pos.
		vec2 newPos = _pos + _vel * deltaTime;

		if (!CollisionCheck(newPos))
		{
			_pos = newPos;
		}
		else
		{
			OnCollide();
		}

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

bool Ball::CollisionCheck(vec2 newPos)
{
	// Collision detection.
	for (int j = 0; j < NUM_BALLS; j++) 
	{
		if (this != balls[j]) 
		{
			float limitSquared = (_radius + balls[j]._radius) * (_radius + balls[j]._radius);
			if (vlen2(newPos - balls[j]._pos) <= limitSquared) 
			{
				balls[j].OnCollide();
				return true;
			}
		}
	}
	return false;
}

void Ball::OnCollide()
{
	// Rebound!
	_vel *= -1.f;
}