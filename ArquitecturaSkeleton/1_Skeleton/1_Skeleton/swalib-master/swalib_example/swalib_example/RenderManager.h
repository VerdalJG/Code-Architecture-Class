#pragma once
#include "Globals.h"
#include "RenderComponent.h"
#include <map>

class TimeManager;
class Sprite;
class Entity;
class Background;
class Widget;

//struct TextureKey
//{
//	const char* filePath;
//	bool screenWrapping;
//
//	// Operator required for hashing and being able to use the find() function
//	bool operator==(const TextureKey& other) const 
//	{
//		return filePath == other.filePath && screenWrapping == other.screenWrapping;
//	}
//
//	// Operator is required for map ordering
//	bool operator<(const TextureKey& other) const 
//	{
//		return std::tie(filePath, screenWrapping) < std::tie(other.filePath, other.screenWrapping);
//	}
//};

class RenderManager
{
public:
	static RenderManager& GetInstance();
	void Initialize(TimeManager* timer);
	void Update();
	void Terminate();

	void DisplayTimerValues();
	void RenderJSONData();
	void RenderBackground(Background* background);
	void RenderSprites();
	void RenderUI();

	void RegisterEntity(Entity* entity);
	void RegisterWidget(Widget* widget);
	void RemoveEntity(Entity* entity);
	void RemoveWidget(Widget* widget);
	void ClearWidgets();
	Sprite* LoadSprite(const std::string& name, const std::string& filePath, const bool& uvWrapping);
	void UnloadAllSprites();

	//GLuint GetTexture(const char* filePath, bool screenWrapping, vec2& dimensions);

private:
	Sprite* GetLoadedSprite(const std::string& name, const std::string& filePath, const bool& uvWrapping);

	std::vector<Sprite*> loadedSprites;
	std::vector<Entity*> entities;
	std::vector<Widget*> widgets;
	TimeManager* timer;
	Background* background;
};


