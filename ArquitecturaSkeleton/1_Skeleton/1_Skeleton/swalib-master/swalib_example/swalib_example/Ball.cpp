#include "Ball.h"
#include "Globals.h"
#include "Render.h"
#include "World.h"

Ball::Ball()
{
	// Set initial sprite and collision values
	SetRadius(16.0f);
	vec2 spriteSize = vec2(radius * 2.0f, radius * 2.0f);
	CreateSprite("data/tyrian_ball.png", false, spriteSize);

	// Randomize initial position and velocity
	SetPosition(vec2(CORE_FRand(0.0 + radius, SCR_WIDTH - radius), CORE_FRand(0.0 + radius, SCR_HEIGHT - radius)));
	SetVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED)));
}

Ball::~Ball()
{
	
}

void Ball::Tick(const float deltaTime)
{
	RunPhysics(deltaTime);
}

void Ball::RunPhysics(const float deltaTime)
{
	// Run ball
	// New Pos.
	vec2 newPosition = position + velocity * deltaTime;
	if (!CollisionCheck(newPosition))
	{
		SetPosition(newPosition);
	}

	// Rebound on margins.
	if (position.x > SCR_WIDTH - radius || position.x < 0 + radius)
	{
		velocity.x *= -1.0;
	}
	if (position.y > SCR_HEIGHT - radius || position.y < 0 + radius)
	{
		velocity.y *= -1.0;
	}
}

bool Ball::CollisionCheck(vec2 newPosition)
{
	// Collision detection.
	World* world = GetWorld();
	for (Entity* entity : world->GetEntities())
	{
		Ball* collidingBall = static_cast<Ball*>(entity);
		if (collidingBall && this != collidingBall)
		{
			float limitSquared = (this->GetRadius() + collidingBall->GetRadius()) * (this->GetRadius() + collidingBall->GetRadius());
			if (vlen2(newPosition - collidingBall->GetPosition()) <= limitSquared)
			{
				OnCollide();
				collidingBall->OnCollide();
				return true;
			}
		}
	}
	return false;
}

void Ball::OnCollide()
{
	// Rebound!
	velocity *= -1.0f;
}