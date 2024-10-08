#pragma once
#include "Globals.h"

class Sprite
{
public:
	Sprite(GLuint texture, vec2 spriteSize);
	~Sprite();

private:
	GLuint texture;
	vec2 size;

public:
	GLuint GetTexture() { return texture; }
	void SetTexture(const char* filePath, bool screenWrapping);

	vec2 GetSize() { return size; }
	void SetSize(vec2 newSize) { size = newSize; }
};

