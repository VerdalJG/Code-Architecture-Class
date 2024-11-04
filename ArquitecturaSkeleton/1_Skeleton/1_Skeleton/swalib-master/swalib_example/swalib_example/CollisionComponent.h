#pragma once
#include "Component.h"
#include "Globals.h"

enum class ColliderType
{
	Circle,
	Box,
	Unknown
};

enum class CollisionLayer;

class CollisionComponent : public Component
{
public:
	CollisionComponent();
	void Tick(float deltaTime) override;
	void CollisionCheck(CollisionComponent* ownerComponent, CollisionComponent* otherComponent);
	virtual void OnAttach() override;

	virtual bool CircleCircleCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) { return false; }
	virtual bool CircleBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) { return false; }
	virtual bool BoxBoxCollisionCheck(CollisionComponent* otherCollider, vec2& collisionNormal, float& depthOfIntersection) { return false; }

	virtual void ReceiveMessage(Message* message) override;

protected:
	vec2 worldPosition;
	vec2 offset;
	ColliderType type;
	CollisionLayer layer;
	bool isTrigger = false;

public:
	vec2 GetWorldPosition() { return worldPosition; }
	void SetWorldPosition(vec2 newPosition) { worldPosition = newPosition; }

	vec2 GetOffset() { return offset; }
	void SetOffset(vec2 newOffset) { offset = newOffset;}

	bool IsTrigger() { return isTrigger; }
	void SetTrigger(bool newIsTrigger) { isTrigger = newIsTrigger; }

	ColliderType GetColliderType() { return type; }
	CollisionLayer GetCollisionLayer() { return layer; }
	void SetCollisionLayer(CollisionLayer newLayer) { layer = newLayer; }
};

