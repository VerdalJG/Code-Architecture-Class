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

public:
	Sprite* GetSprite() { return sprite; }
	void SetSprite(Sprite* newSprite) { sprite = newSprite; }
	void SetSprite(const char* filePath, bool screenWrapping);
};

