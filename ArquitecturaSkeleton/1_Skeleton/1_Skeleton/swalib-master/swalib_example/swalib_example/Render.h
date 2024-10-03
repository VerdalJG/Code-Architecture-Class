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
	void RenderTiled(Sprite* Sprite);
	void RenderSprites();

	GLuint LoadSprite(const char* FilePath, bool ScreenWrapping);
	void UnloadSprite(GLuint TextureID);

	std::vector<Entity*> Entities;

private:
	TimeManager* Timer;
	Background* background;
};
