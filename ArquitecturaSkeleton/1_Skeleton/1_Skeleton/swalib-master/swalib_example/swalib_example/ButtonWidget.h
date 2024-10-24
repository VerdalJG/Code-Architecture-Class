#pragma once
#include <functional>
#include <vector>
#include "Widget.h"

class ButtonWidget : public Widget
{
public:
	// Define a delegate type that represents the callback signature
	using Delegate = std::function<void()>;

	// Function to add a listener (register callback)
	void AddListener(Delegate listener);

	void Select();

private:
	// A list to store all the listeners (callbacks)
	std::vector<Delegate> listeners;

	// Notify all registered listeners
	void Broadcast();
};

