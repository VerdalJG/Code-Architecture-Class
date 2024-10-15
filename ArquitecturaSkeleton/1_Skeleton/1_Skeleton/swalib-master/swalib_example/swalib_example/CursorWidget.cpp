#include "CursorWidget.h"

CursorWidget::CursorWidget()
{
}

CursorWidget::~CursorWidget()
{
}

void CursorWidget::AddSelectableWidget(Widget* widget)
{
	selectableWidgets.push_back(widget);
}

void CursorWidget::SelectNextWidget(bool advanceSelection)
{
	if (selectableWidgets.size() > 0)
	{
		advanceSelection ? selectedWidget++ : selectedWidget--;
		selectedWidget %= static_cast<unsigned int>(selectableWidgets.size()); // avoid array out of bounds
		position = selectableWidgets[selectedWidget]->GetPosition() + offsetFromSelection;
	}
}