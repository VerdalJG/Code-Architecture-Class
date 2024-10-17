#pragma once
#include "Globals.h"
#include "RenderComponent.h"
#include <map>

class TimeManager;
class Sprite;
class Entity;
class Background;
class Widget;

struct TextureKey
{
	const char* filePath;
	bool screenWrapping;

	// Operator required for hashing and being able to use the find() function
	bool operator==(const TextureKey& other) const 
	{
		return filePath == other.filePath && screenWrapping == other.screenWrapping;
	}

	// Operator is required for map ordering
	bool operator<(const TextureKey& other) const 
	{
		return std::tie(filePath, screenWrapping) < std::tie(other.filePath, other.screenWrapping);
	}
};

class RenderEngine
{
public:
	static RenderEngine& GetInstance();
	void Initialize(TimeManager* timer);
	void Update();
	void Terminate();

	void DisplayTimerValues();
	void RenderJSONData();
	void RenderTiled(Sprite* sprite);
	void RenderSprites();
	void RenderUI();

	void RegisterEntity(Entity* entity);
	void RegisterWidget(Widget* widget);
	GLuint GetTexture(const char* filePath, bool screenWrapping);
	void UnloadTextures();

private:
	std::map<TextureKey, GLuint> loadedTextures;
	std::vector<Entity*> entities;
	std::vector<Widget*> widgets;
	TimeManager* timer;
	Background* background;
};


