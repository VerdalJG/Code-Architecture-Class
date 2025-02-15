#include "CursorWidget.h"
#include "ButtonWidget.h"
#include "RenderManager.h"

CursorWidget::CursorWidget() : 
	sprite(nullptr)
{
}

CursorWidget::~CursorWidget()
{
}

void CursorWidget::AddSelectableWidget(Widget* widget)
{
	selectableWidgets.push_back(widget);
	if (selectableWidgets.size() == 1)
	{
		SelectNextWidget(true);
	}
}

void CursorWidget::SelectNextWidget(bool advanceSelection)
{
	if (selectableWidgets.size() > 0)
	{
		advanceSelection ? selectedWidget++ : selectedWidget--;
		selectedWidget %= static_cast<unsigned int>(selectableWidgets.size()); // avoid array out of bounds
		worldPosition = selectableWidgets[selectedWidget]->GetWorldPosition() + offsetFromSelection;
	}
}

void CursorWidget::MakeSelection()
{
	if (selectableWidgets.size() <= 0)
	{
		return;
	}

	for (Widget* widget : selectableWidgets[selectedWidget]->GetChildrenWidgets())
	{
		ButtonWidget* button = dynamic_cast<ButtonWidget*>(widget);
		if (button)
		{
			button->Select();
		}
	}
}

void CursorWidget::Tick(float deltaTime)
{
	accumulatedTime += deltaTime;

	// Wrap the time to avoid precision loss (using 2 * PI for a full cycle)
	float wrapThreshold = 2.0f * 3.14159;  // 2 * PI
	if (accumulatedTime > wrapThreshold) 
	{
		accumulatedTime = fmod(accumulatedTime, wrapThreshold);
	}

	selectionHoveringDistance = MAX_SELECTION_HOVER * sinf(accumulatedTime * 3);
	worldPosition = selectableWidgets[selectedWidget]->GetWorldPosition() + offsetFromSelection + vec2(selectionHoveringDistance, 0);
}

void CursorWidget::SetOffset(vec2 newOffset)
{
	offsetFromSelection = newOffset;
	if (selectableWidgets.size() > 0)
	{
		worldPosition = selectableWidgets[selectedWidget]->GetWorldPosition() + offsetFromSelection;
	}
	else
	{
		worldPosition = offsetFromSelection;
	}
}

void CursorWidget::SetSprite(Sprite* newSprite)
{
	sprite = newSprite;
}
