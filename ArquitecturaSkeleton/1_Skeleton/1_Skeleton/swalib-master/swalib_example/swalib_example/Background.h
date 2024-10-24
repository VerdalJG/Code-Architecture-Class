#pragma once
#include "Globals.h"
class Sprite;

class Background
{
public:
	Background();
	~Background();

private:
	Sprite* sprite;
	bool isTiledBackground = false;

public:
	Sprite* GetTexture() { return sprite; }
	void SetSprite(Sprite* newSprite) { sprite = newSprite; }

	bool IsTiled() { return isTiledBackground; }
	void SetBackgroundTiledMode(bool isTiled) { isTiledBackground = isTiled; }
};

