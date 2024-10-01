#pragma once
#include "GameManager.h"
#include "Time.h"

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

private: 
	Timer Timer;
};
