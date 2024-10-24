#include "Widget.h"

Widget::Widget()
{
}

Widget::~Widget()
{
	for (Widget* widget : childWidgets)
	{
		delete(widget);
	}
}

void Widget::AttachToWidget(Widget* parent)
{
	// Detach from the current parent, if any
	if (parentWidget)
	{
		parentWidget->RemoveChildWidget(this);
	}

	// Attach to the new parent
	parentWidget = parent;
	if (parent)
	{
		parent->RegisterChildWidget(this);
	}
}

void Widget::RegisterChildWidget(Widget* child)
{
	if (child && std::find(childWidgets.begin(), childWidgets.end(), child) == childWidgets.end())
	{
		childWidgets.push_back(child);
	}
}

void Widget::RemoveChildWidget(Widget* child)
{
	auto iterator = std::find(childWidgets.begin(), childWidgets.end(), child);
	if (iterator != childWidgets.end()) // Found the child widget
	{
		child->parentWidget = nullptr;
		childWidgets.erase(iterator);
	}
}
