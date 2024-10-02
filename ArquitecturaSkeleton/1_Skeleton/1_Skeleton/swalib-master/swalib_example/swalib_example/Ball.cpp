#include "Ball.h"
#include "Globals.h"
#include "Render.h"

Ball::Ball()
{
	// Set initial sprite and collision values
	SetRadius(16.0f);
	vec2 SpriteSize = vec2(Radius * 2.0f, Radius * 2.0f);
	CreateSprite("data/tyrian_ball.png", false, SpriteSize);

	// Randomize initial position and velocity
	SetPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
	SetVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
}

Ball::~Ball()
{
	
}

void Ball::Tick(const float deltaTime)
{
	// Run ball
	// New Pos.
	vec2 NewPosition = Position + Velocity * deltaTime;
	SetPosition(NewPosition);

	// Rebound on margins.
	if (Position.x > SCR_WIDTH - Radius || Position.x < 0 + Radius)
	{
		Velocity.x *= -1.0;
	}
	if (Position.y > SCR_HEIGHT - Radius || Position.y < 0 + Radius)
	{
		Velocity.y *= -1.0;
	}
	
}

void Ball::OnCollide()
{
	// Rebound!
	Velocity *= -1.f;
}