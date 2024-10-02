#pragma once
#include "Globals.h"

class Sprite
{
public:
	Sprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize);
	~Sprite();

private:
	GLuint Texture;
	vec2 Size;
	vec2 Offset;

public:
	GLuint GetTexture() { return Texture; }
	void SetTexture(const char* FilePath, bool ScreenWrapping);

	vec2 GetSize() { return Size; }
	void SetSize(vec2 NewSize) { Size = NewSize; }

	vec2 GetOffset() { return Offset; }
	void SetOffset(vec2 NewOffset) { Offset = NewOffset; }
};

