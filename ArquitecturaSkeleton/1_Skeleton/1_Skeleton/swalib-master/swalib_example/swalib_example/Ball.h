#pragma once
#include "Globals.h"
#include "Actor.h"

class Ball : public Actor
{
public:
	Ball();
	~Ball() override;

	virtual void Tick(const float deltaTime) override;
	virtual void OnCollide(Entity* otherEntity) override;
	void Split();

private:
	int splitCounter = 3;
	const int MAX_SPLITS = 3;
	const int MAX_SIZE_SCALE = 2.0f;
	const vec2 VELOCITY_ON_SPLIT = vec2(30.0f, 30.0f);
	//const float radius = 16.0f;
	//const float MAX_BALL_SPEED = 80.0f;	// Max vel. of ball. (pixels/?).
};


