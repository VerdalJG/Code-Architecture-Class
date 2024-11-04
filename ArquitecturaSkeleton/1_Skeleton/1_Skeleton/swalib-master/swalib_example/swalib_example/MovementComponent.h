#pragma once
#include "Component.h"
#include "Globals.h"

class MovementComponent : public Component
{
public:
	MovementComponent();
	MovementComponent(const MovementComponent& copy); // for copying
	void Tick(float deltaTime) override;
	virtual void ReceiveMessage(Message* message) override;


private:
	vec2 worldPosition;	// Position.
	vec2 previousMovement;// Used to reverse the movement that occurred in this frame to resolve collision
	vec2 velocity;	// Velocity.
	bool gravity = false;


public:
	vec2 GetWorldPosition() { return worldPosition; }
	void SetWorldPosition(vec2 worldPosition) { this->worldPosition = worldPosition; }

	vec2 GetVelocity() { return velocity; }
	void SetVelocity(vec2 velocity) { this->velocity = velocity; }

	bool IsGravityOn() { return gravity; }
	void SetGravity(bool enabled) { gravity = enabled; }
	
	virtual Component* Clone() override;
};

