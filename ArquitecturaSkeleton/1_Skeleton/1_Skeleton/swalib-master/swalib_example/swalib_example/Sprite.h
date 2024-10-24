#pragma once
#include "Globals.h"

class RenderEngine;

class Sprite
{
public:
	Sprite(const Sprite& copy) = delete;
	Sprite& operator=(const Sprite&) = delete;

	friend class RenderEngine;

private:
	std::string name;
	std::string filePath;
	bool uvWrapping;
	GLuint texture;
	vec2 size;
	int referenceCount;

	// Private constructor to restrict direct instantiation
	Sprite(std::string name, std::string filePath, bool uvWrapping, vec2 dimensions);
	~Sprite();

public:
	GLuint GetTexture() const { return texture; }
	void SetTexture(GLuint newTexture) { texture = newTexture; }

	vec2 GetSize() const { return size; }

	std::string GetName() const { return name; }
	std::string GetFilePath() const { return filePath; }
	bool GetWrapping() const { return uvWrapping; }

	// Manage reference counting
	void IncrementRef() { referenceCount++; }
	void DecrementRef() { referenceCount--; }

	// Check if the sprite can be deleted
	bool CanDelete() const { return referenceCount == 0; }
};

