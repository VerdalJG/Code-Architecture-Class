#pragma once
#include "Actor.h"
class Stair : public Actor
{
public:
	Stair();
	virtual ~Stair() override;

private:
	vec2 stairBottom;
	vec2 stairTop;

public:
	vec2 GetBottomPosition() { return stairBottom; }
	vec2 GetTopPosition() { return stairTop; }

	void SetBottomPosition(vec2 newPosition) { stairBottom = newPosition; }
	void SetTopPosition(vec2 newPosition) { stairTop = newPosition; }
};

