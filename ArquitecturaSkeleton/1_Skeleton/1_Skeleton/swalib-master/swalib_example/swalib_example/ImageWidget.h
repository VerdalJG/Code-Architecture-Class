#pragma once
#include "Widget.h"

class Sprite;

class ImageWidget : public Widget
{
public:
	ImageWidget();
	~ImageWidget() override;

private: 
	Sprite* sprite;
	vec2 scale;

public:
	Sprite* GetSprite() { return sprite; }
	void SetSprite(Sprite* newSprite);

	vec2 GetScale() { return scale; }
	void SetScale(vec2 newScale) { scale = newScale; }
};

