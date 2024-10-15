#pragma once
#include "Globals.h"
#include "ImageWidget.h"

class CursorWidget : public ImageWidget
{
public:
	CursorWidget();
	~CursorWidget() override;

	void AddSelectableWidget(Widget* widget);
	void SelectNextWidget(bool advanceSelection);

private:
	vec2 offsetFromSelection;
	std::vector<Widget*> selectableWidgets;
	unsigned int selectedWidget = 0;

public:
	vec2 GetOffset() { return offsetFromSelection; };
	void SetOffset(vec2 newOffset) { offsetFromSelection = newOffset; }
};

