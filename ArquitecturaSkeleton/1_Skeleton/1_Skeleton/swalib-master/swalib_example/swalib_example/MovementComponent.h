#pragma once
#include "Component.h"
#include "Globals.h"
class MovementComponent : public Component
{
public:
	MovementComponent();
	void Tick(float deltaTime) override;
	virtual void ReceiveMessage(Message* message) override;


private:
	vec2 position;	// Position.
	vec2 previousMovement;// Used to reverse the movement that occurred in this frame to resolve collision
	vec2 velocity;	// Velocity.


public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 position) { this->position = position; }

	vec2 GetVelocity() { return velocity; }
	void SetVelocity(vec2 velocity) { this->velocity = velocity; }
};

