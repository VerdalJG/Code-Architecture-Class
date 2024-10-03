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
	void Initialize(TimeManager* Timer);
	void Update();
	void Terminate();

	void DisplayTimerValues();
	void RenderTiled(Sprite* _sprite);
	void RenderSprites();

	void RegisterEntity(Entity* _entity);
	GLuint LoadSprite(const char* FilePath, bool ScreenWrapping);
	void UnloadSprite(GLuint TextureID);



private:
	std::vector<Entity*> entities;
	TimeManager* timer;
	Background* background;
};
