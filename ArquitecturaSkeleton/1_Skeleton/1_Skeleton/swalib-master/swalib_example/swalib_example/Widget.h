#pragma once
#include "Globals.h"

class Widget
{
public:
	Widget();
	virtual void Tick(float deltaTime) {};
	virtual ~Widget();

protected:
	Widget* parentWidget = nullptr;
	std::vector<Widget*> childWidgets;

	bool isVisible = true;
	vec2 worldPosition;

public:
	bool GetVisibility() { return isVisible; }
	void SetVisibility(bool visibility) { isVisible = visibility; }

	vec2 GetWorldPosition() { return worldPosition; }
	void SetWorldPosition(vec2 newPosition) { worldPosition = newPosition; }

	void AttachToWidget(Widget* parent);
	void RegisterChildWidget(Widget* child);
	void RemoveChildWidget(Widget* child);
	std::vector<Widget*> GetChildrenWidgets() { return childWidgets; }
};

