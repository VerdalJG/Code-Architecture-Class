#pragma once
#include "Globals.h"

class Widget
{
public:
	Widget();
	virtual void Tick(float deltaTime) {};
	virtual ~Widget() = default;

protected:
	bool isVisible = true;
	bool isSelectable = false;
	vec2 position;

public:
	bool GetVisibility() { return isVisible; }
	void SetVisibility(bool visibility) { isVisible = visibility; }

	bool GetSelectability() { return isSelectable; }
	void SetSelectability(bool selectability) { isSelectable = selectability; }

	vec2 GetPosition() { return position; }
	void SetPosition(vec2 newPosition) { position = newPosition; }
};

