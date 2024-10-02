#include "Background.h"
#include "Globals.h"
#include "Render.h"

Background::Background()
{
	vec2 SpriteSize = vec2(128.0f, 128.0f);
	CreateSprite("data/circle-bkg-128.png", true, SpriteSize);
}

Background::~Background()
{
}
