#pragma once
#include "Globals.h"

class Widget;
class CursorWidget;

class UIManager
{
public:
	static UIManager& GetInstance();
	void Terminate();

	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);
	void ResetUI();

	void NavigateUp();
	void NavigateDown();
	void Confirm();
	void SetControllingWidget(CursorWidget* widget);

	bool IsActive() { return isActive; }
	void SetActive(bool newIsActive);

private:
	bool isActive = false;
	std::vector<Widget*> widgets;
	CursorWidget* controllingWidget;
};

