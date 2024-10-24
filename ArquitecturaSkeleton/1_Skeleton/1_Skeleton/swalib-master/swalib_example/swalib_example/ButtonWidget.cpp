#include "ButtonWidget.h"

void ButtonWidget::AddListener(Delegate listener)
{
	listeners.push_back(listener);
}

void ButtonWidget::Select()
{
	Broadcast(); // Notify all listeners when the button is selected
}

void ButtonWidget::Broadcast()
{
	for (const auto& listener : listeners)
	{
		if (listener) // Check if the listener is valid
		{
			listener(); // Call the listener function
		}
	}
}
