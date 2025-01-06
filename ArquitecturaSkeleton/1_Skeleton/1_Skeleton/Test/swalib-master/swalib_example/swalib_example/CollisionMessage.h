#pragma once
#include "Message.h"
#include "Globals.h"

class CollisionComponent;

enum class CollisionType
{
	None,
	ComponentCollision, // Collision with another component
	ScreenEdgeCollision // Collision with screen edge
};


enum class CollisionDirection
{
	None,
	Horizontal,
	Vertical
};

class CollisionMessage : public Message
{
public:
	CollisionMessage();
	CollisionMessage(CollisionComponent* other);
	CollisionMessage(CollisionDirection direction);

	CollisionComponent* collidingComponent;
	CollisionType collisionType;
	CollisionDirection collisionDirection; // Only relevant if type is ScreenEdgeCollision
	vec2 resolvedPosition;
};

