#include "Ball.h"
#include "Globals.h"

Ball::Ball()
{
	// renderer 
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

	SetPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
	SetVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
	SetRadius(16.f);
	SetSprite(texsmallball); // should call the renderer or smth
}

Ball::~Ball()
{
	
}

void Ball::Tick(const float deltaTime)
{
	// Run ball

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

void Ball::OnCollide()
{
	// Rebound!
	_vel *= -1.f;
}