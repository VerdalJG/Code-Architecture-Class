#pragma once
#include "Component.h"
#include "Globals.h"


class CollisionComponent : public Component
{
public:
	CollisionComponent();
	void Tick(float deltaTime) override;
	void CollisionCheck();
	void ScreenLimitCheck();
	virtual void ReceiveMessage(Message* message) override;
	

private:
	vec2 position;	// Position.
	float radius;	// Radius.

public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 position) { this->position = position;}

	float GetRadius() { return radius; }
	void SetRadius(float radius) { this->radius = radius; }


};

