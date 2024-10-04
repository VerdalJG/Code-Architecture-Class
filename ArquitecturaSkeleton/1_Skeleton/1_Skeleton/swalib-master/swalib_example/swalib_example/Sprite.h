#pragma once
#include "Globals.h"

class Sprite
{
public:
	Sprite(const char* filePath, bool screenWrapping, vec2 spriteSize);
	~Sprite();

private:
	GLuint texture;
	vec2 size;
	vec2 offset;

public:
	GLuint GetTexture() { return texture; }
	void SetTexture(const char* filePath, bool screenWrapping);

	vec2 GetSize() { return size; }
	void SetSize(vec2 newSize) { size = newSize; }

	vec2 GetOffset() { return offset; }
	void SetOffset(vec2 newOffset) { offset = newOffset; }
};

