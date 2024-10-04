#pragma once
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
	void UnloadSprite(GLuint textureID);



private:
	std::vector<Entity*> entities;
	TimeManager* timer;
	Background* background;
};
