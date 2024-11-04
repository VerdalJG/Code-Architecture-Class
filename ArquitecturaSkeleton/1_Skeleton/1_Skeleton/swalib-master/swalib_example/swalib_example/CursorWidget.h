#pragma once
#include "Globals.h"
#include "Widget.h"
#include "Sprite.h"

class CursorWidget : public Widget
{
public:
	CursorWidget();
	~CursorWidget() override;

	void AddSelectableWidget(Widget* widget);
	void SelectNextWidget(bool advanceSelection);
	void MakeSelection();

protected:
	virtual void Tick(float deltaTime) override;

private:
	Sprite* sprite;
	vec2 scale = vec2(1.0f, 1.0f);

	vec2 offsetFromSelection;
	float selectionHoveringDistance = 0;
	const float MAX_SELECTION_HOVER = 10;
	std::vector<Widget*> selectableWidgets;
	unsigned int selectedWidget = -1;
	float accumulatedTime = 0;

public:
	vec2 GetOffset() { return offsetFromSelection; };
	void SetOffset(vec2 newOffset);

	Sprite* GetSprite() { return sprite; }
	void SetSprite(Sprite* newSprite);

	vec2 GetScale() { return scale; }
	void SetScale(vec2 newScale) { scale = newScale; }
};



