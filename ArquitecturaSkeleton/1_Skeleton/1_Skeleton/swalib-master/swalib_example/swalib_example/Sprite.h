#pragma once
#include "Globals.h"

class Sprite
{
public:
	GLuint GetTexture() { return Texture; }
	GLuint SetTexture(GLuint NewTexture);
	
	vec2 GetSize() { return Size; }
	vec2 SetSize(vec2 NewSize) { Size = NewSize; }

	vec2 GetPosition() { return Position; }
	vec2 SetPosition(vec2 NewPosition) { Position = NewPosition; }

private:
	GLuint Texture;
	vec2 Size;
	vec2 Position;
};

