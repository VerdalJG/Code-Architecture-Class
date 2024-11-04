#include "Player.h"
#include "MovementComponent.h"
#include "Solid.h"
#include "Harpoon.h"
#include "World.h"
#include "BoxCollisionComponent.h"
#include "RenderComponent.h"
#include "Ball.h"
#include "WorldManager.h"


Player::Player() :
	movementComponent(nullptr)
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	movementComponent = GetComponent<MovementComponent>();
	collisionComponent = GetComponent<BoxCollisionComponent>();
	renderComponent = GetComponent<RenderComponent>();
	harpoon = GetWorld()->FindActor<Harpoon>();
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
}

void Player::OnCollide(Entity* other)
{
	Solid* wall = dynamic_cast<Solid*>(other);
	if (wall)
	{
		movementComponent->SetVelocity(vec2());

		if (wall->GetName() == "BottomWall")
		{
			movementComponent->SetGravity(false);
		}
	}

	Ball* ball = dynamic_cast<Ball*>(other);
	if (ball)
	{
		//WorldManager::GetInstance().LoadWorld(WorldType::GameWorld);
	}
}

void Player::OnTrigger(Entity* other)
{
}

void Player::Move(vec2 direction)
{
	vec2 currentVelocity = movementComponent->GetVelocity();
	if (direction != vec2())
	{
		if (canClimb && direction.y != 0)
		{
			float xSpeed = 0;
			float ySpeed = climbingSpeed * direction.y;
			movementComponent->SetGravity(false);
			currentVelocity = vec2(xSpeed, ySpeed);
			isClimbing = true;
		}
		else
		{
			float xSpeed = currentVelocity.x + (direction.x * acceleration);
			float ySpeed = isClimbing ? 0 : currentVelocity.y; // Keep same value for gravity;
			currentVelocity = vec2(xSpeed, ySpeed);
		}


		currentVelocity = vec2clamp(currentVelocity, vec2(-maxWalkingVelocity, -maxFallSpeed), vec2(maxWalkingVelocity, maxFallSpeed));
		movementComponent->SetVelocity(currentVelocity);

		if (currentVelocity.x != 0 && currentVelocity.y == 0)
		{
			renderComponent->SetCurrentAnimation("Walking");
		}
		if (currentVelocity.y != 0 && currentVelocity.x == 0)
		{
			renderComponent->SetCurrentAnimation("Climbing");
		}
		isShooting = false;
	}
	else
	{
		if (isClimbing)
		{
			currentVelocity = direction;
		}
		else
		{
			currentVelocity.x = direction.x;
		}
		
		movementComponent->SetVelocity(currentVelocity);
		if (!isShooting)
		{
			renderComponent->SetCurrentAnimation("Idle");
		}
	}
}

void Player::ShootHarpoon()
{
	if (!harpoon->IsOnScreen())
	{
		vec2 floorPosition = vec2(worldPosition.x, worldPosition.y - collisionComponent->GetHalfExtents().y);
		harpoon->Fire(floorPosition);
		renderComponent->SetCurrentAnimation("Shooting");
		isShooting = true;
		movementComponent->SetGravity(true);
		canClimb = false;
		isClimbing = false;
	}
}
