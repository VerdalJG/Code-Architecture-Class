#include "UIManager.h"
#include "RenderManager.h"
#include "CursorWidget.h"

UIManager& UIManager::GetInstance()
{
	static UIManager instance;
	return instance;
}

void UIManager::Terminate()
{
	for (Widget* widget : widgets)
	{
		delete(widget);
	}
}

void UIManager::AddWidget(Widget* widget)
{
	if (widget)
	{
		widgets.push_back(widget);
		RenderEngine::GetInstance().RegisterWidget(widget);
	}
}

void UIManager::RemoveWidget(Widget* widget)
{
	if (widget)
	{
		widgets.erase(std::remove(widgets.begin(), widgets.end(), widget), widgets.end());
		RenderEngine::GetInstance().RemoveWidget(widget);
		delete(widget);
	}
}

void UIManager::ResetUI()
{
	for (Widget* widget : widgets)
	{
		delete(widget);
	}

	RenderEngine::GetInstance().ClearWidgets();
	widgets.clear();
}

void UIManager::NavigateUp()
{
	controllingWidget->SelectNextWidget(false);
}

void UIManager::NavigateDown()
{
	controllingWidget->SelectNextWidget(true);
}

void UIManager::Confirm()
{
	controllingWidget->MakeSelection();
}

void UIManager::SetControllingWidget(CursorWidget* widget)
{
	if (widget)
	{
		controllingWidget = widget;
	}
}

void UIManager::SetActive(bool newIsActive)
{
	isActive = newIsActive;
}
