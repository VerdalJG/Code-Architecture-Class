#include "Harpoon.h"
#include "HarpoonBody.h"
#include "RenderComponent.h"
#include "Sprite.h"
#include "MovementComponent.h"
#include "BoxCollisionComponent.h"
#include "Ball.h"
#include "GameManager.h"

Harpoon::Harpoon()
{
}

Harpoon::~Harpoon()
{
}

void Harpoon::BeginPlay()
{
    movementComponent = GetComponent<MovementComponent>();
    collisionComponent = GetComponent<BoxCollisionComponent>();
    if (bodyEntity)
    {
        bodyEntity->SetHarpoon(this);
    }
}

void Harpoon::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    if (IsOnScreen())
    {
        float topEdgeBodyPosition = GetWorldPosition().y - collisionComponent->GetHalfExtents().y;
        float distanceTravelled = topEdgeBodyPosition - floorHeight;
        vec2 bodyScale = vec2(1, distanceTravelled / (bodyEntity->GetBoxCollider()->GetHalfExtents().y * 2));
        bodyEntity->SetWorldScale(bodyScale);
    }
}

void Harpoon::OnCollide(Entity* other)
{
    ResetHarpoon();

    Ball* ball = dynamic_cast<Ball*>(other);
    if (ball)
    {
        // add some score here?
        GameManager::GetInstance().AddScore();
    }
}

void Harpoon::ResetHarpoon()
{
    // Move off-screen
    SetWorldPosition(vec2(800, 800));
    movementComponent->SetVelocity(vec2(0, 0));

    bodyEntity->SetWorldPosition(vec2(800, 800));
    bodyEntity->SetWorldScale(vec2(1, 1));
    bodyEntity->GetComponent<MovementComponent>()->SetVelocity(vec2(0, 0));
}

bool Harpoon::IsOnScreen()
{
    return worldPosition.x > 0 && worldPosition.x < SCR_WIDTH && worldPosition.y > 0 && worldPosition.y < SCR_HEIGHT;
}

void Harpoon::Fire(vec2 floorPosition)
{
    floorHeight = floorPosition.y; // Store for future calculations

    vec2 bodyHalfExtents = bodyEntity->GetBoxCollider()->GetHalfExtents();
    vec2 headHalfExtents = collisionComponent->GetHalfExtents();

    // Place the harpoon body
    vec2 harpoonStartPosition = vec2(floorPosition.x, floorHeight + bodyHalfExtents.y);
    bodyEntity->SetWorldPosition(harpoonStartPosition);
    bodyEntity->SetWorldScale(vec2(1, 1));
    bodyEntity->GetMovementComponent()->SetVelocity(vec2(0, bulletSpeed / 2)); // Divide by two to account for growing

    // Place the harpoon head
    vec2 harpoonHeadStartHeight = vec2(harpoonStartPosition.x, harpoonStartPosition.y + bodyHalfExtents.y + headHalfExtents.y);
    SetWorldPosition(harpoonHeadStartHeight);
    movementComponent->SetVelocity(vec2(0.0f, bulletSpeed));
}
