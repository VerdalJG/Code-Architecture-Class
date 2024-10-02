#pragma once

class Timer;
class Sprite;

class Renderer
{
public:
	static Renderer& GetInstance();
	void Initialize();
	void Slot();
	void Tick(float deltaTime);
	void Terminate();
	void RenderBackground();
	void RenderBalls();
	void RenderSprites();
	GLuint LoadSprite(const char* FilePath, bool ScreenWrapping);

	std::vector<Sprite*> Sprites;

private:
	Timer* Timer;
};
