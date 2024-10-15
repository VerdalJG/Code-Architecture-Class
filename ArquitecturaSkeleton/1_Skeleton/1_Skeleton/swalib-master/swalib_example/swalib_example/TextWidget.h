#pragma once
#include "Widget.h"
#include <string>

class TextWidget : public Widget
{
public:
	TextWidget();
	~TextWidget() override;

private:
	std::string text;
	// normally would have a font variable but not necessary for this project

public:
	std::string GetText() { return text; }
	void SetText(std::string newText) { text = newText; }
};

