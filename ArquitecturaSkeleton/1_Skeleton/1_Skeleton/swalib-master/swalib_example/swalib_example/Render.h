#pragma once
#include <unordered_map>
#include <functional>
#include "Globals.h"

class TimeManager;
class Sprite;
class Entity;
class Background;

class RenderEngine
{
public:
	static RenderEngine& GetInstance();
	void Initialize(TimeManager* timer);
	void Update();
	void Terminate();

	void DisplayTimerValues();
	void RenderTiled(Sprite* sprite);
	void RenderSprites();

	void RegisterEntity(Entity* entity);
	GLuint LoadSprite(const char* filePath, bool screenWrapping);
	void UnloadSprites();

	GLuint ballTexture;
	GLuint backgroundTexture;

private:

	std::vector<Entity*> entities;
	TimeManager* timer;
	Background* background;
};


