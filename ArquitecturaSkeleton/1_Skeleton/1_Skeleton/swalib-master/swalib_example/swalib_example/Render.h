#pragma once

class Timer;
class Sprite;
class Entity;

class Renderer
{
public:
	static Renderer& GetInstance();
	void Initialize();
	void Slot();
	void Tick(float deltaTime);
	void Terminate();
	void RenderTiled();
	void RenderBalls();
	void RenderSprites();
	GLuint LoadSprite(const char* FilePath, bool ScreenWrapping);
	void UnloadSprite(GLuint TextureID);

	std::vector<Entity*> Entities;

private:
	Timer* Timer;
};
