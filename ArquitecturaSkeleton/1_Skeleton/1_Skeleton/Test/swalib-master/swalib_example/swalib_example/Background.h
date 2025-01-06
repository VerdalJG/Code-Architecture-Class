#pragma once
#include "Globals.h"
class Sprite;

class Background
{
public:
	Background(const char* filePath, bool screenWrapping);
	~Background();

	Sprite* sprite;
};

