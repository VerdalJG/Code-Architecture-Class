#pragma once
#include "Globals.h"
#include "Actor.h"

class Ball : public Actor
{
public:
	Ball();
	~Ball() override;

	virtual void Tick(const float deltaTime) override;

private:
	//const float radius = 16.0f;
	//const float MAX_BALL_SPEED = 80.0f;	// Max vel. of ball. (pixels/?).
};


