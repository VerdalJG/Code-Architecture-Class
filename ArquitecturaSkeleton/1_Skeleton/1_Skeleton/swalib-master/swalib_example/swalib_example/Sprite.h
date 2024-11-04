#pragma once
#include "Globals.h"

class RenderManager;

enum class SpriteType
{
	None,
	Individual,
	SpriteSheet,
};

struct UVMapping
{
	float u0, v0, u1, v1 = 0;

	UVMapping()
	{
		float u0 = 0;
		float v0 = 0;
		float u1 = 0;
		float v1 = 0;
	}

	UVMapping(float u0, float v0, float u1, float v1)
	{
		this->u0 = u0;
		this->v0 = v0;
		this->u1 = u1;
		this->v1 = v1;
	}
};

class Sprite
{
public:
	using CallbackFunction = void (*)(Sprite&, float);
	friend class RenderManager;
	friend class Animation;

	Sprite(const Sprite& copy) = delete;
	Sprite& operator=(const Sprite&) = delete;
	void ProcessSpriteSheet();


private:
	// Base Data
	std::string name;
	std::string filePath;
	bool uvWrapping;
	GLuint texture;
	vec2 size;
	SpriteType type = SpriteType::None;

	// Data for memory control
	int referenceCount = 0;

	// Sprite Sheet properties
	vec2 spriteSheetDimensions; // Amount of columns (x) and rows (y) of sprites
	vec2 padding; // Amount of space in between sprites
	std::vector<UVMapping> subSpriteUVs; // UVs of each individual sub-sprite

	// Event handling
	CallbackFunction onSpriteSetDelegate = nullptr;
	void* userData = nullptr;


	// Private constructor to restrict direct instantiation

	// Individual Sprite
	Sprite(std::string spriteName, std::string filePath, bool uvWrapping, vec2 dimensions);

	// Sprite sheet
	Sprite(std::string spriteName, std::string filePath, bool uvWrapping, vec2 dimensions, vec2 spritePadding, vec2 sheetLayout = vec2(1,1));

	// RenderManager takes charge of deletion
	~Sprite();

public:
	std::string GetName() const { return name; }
	std::string GetFilePath() const { return filePath; }
	bool GetWrapping() const { return uvWrapping; }

	GLuint GetTextureID() const { return texture; }
	void SetTextureID(GLuint newTexture) { texture = newTexture; }

	vec2 GetSize() const { return size; }

	void* GetUserData() { return userData; }
	void SetUserData(void* data) { userData = data; }

	std::vector<UVMapping> GetUVCoordinates() const { return subSpriteUVs; }
	vec2 GetSpriteSheetLayout() { return spriteSheetDimensions; }
	UVMapping GetSubSpriteUVs(int frame);

	// For callbacks and event handling
	void SetCallback(CallbackFunction function) { onSpriteSetDelegate = function; };

	// Manage reference counting
	void IncrementRef() { referenceCount++; }
	void DecrementRef() { referenceCount--; }

	// Check if the currentSprite can be deleted
	bool CanDelete() const { return referenceCount == 0; }
};

