#pragma once
#include "Message.h"
#include "Globals.h"

class CollisionComponent;


class CollisionMessage : public Message
{
public:
	CollisionMessage(CollisionComponent* other, vec2 collisionNormal, float depthOfIntersection);

	vec2 normal;
	float depth;
	CollisionComponent* collidingComponent;
};

