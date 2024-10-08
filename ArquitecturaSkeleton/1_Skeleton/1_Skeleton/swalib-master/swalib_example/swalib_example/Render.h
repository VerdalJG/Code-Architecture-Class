#pragma once
#include "Globals.h"
#include "RenderComponent.h"

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
	void RenderJSONData();
	void RenderTiled(Sprite* sprite);
	void RenderSprites();

	void RegisterEntity(Entity* entity);
	GLuint LoadTexture(const char* filePath, bool screenWrapping);
	void UnloadTextures();

	GLuint ballTexture;
	GLuint backgroundTexture;

private:

	std::vector<Entity*> entities;
	TimeManager* timer;
	Background* background;
};


