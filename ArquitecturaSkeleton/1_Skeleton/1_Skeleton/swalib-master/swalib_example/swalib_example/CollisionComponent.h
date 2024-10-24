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
	vec2 position;
	vec2 offset;
	float radius;	

public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 newPosition) { position = newPosition; }

	vec2 GetOffset() { return offset; }
	void SetOffset(vec2 newOffset) { offset = newOffset;}

	float GetRadius() { return radius; }
	void SetRadius(float newRadius) { radius = newRadius; }


};

