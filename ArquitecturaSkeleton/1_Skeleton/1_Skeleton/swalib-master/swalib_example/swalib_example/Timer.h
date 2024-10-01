#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	bool ShouldTick();
	float GetFixedTickRate();
	void UpdateTime();
	double GetFPS() { return FPS; }
	double GetTime();
	double GetLogicTime() { return logicTime; }
	

private:
	
	void HandleDeathSpiral();

	double FPS;
	double deltaTime;
	double accumulatedTime;
	double logicTime;
	LARGE_INTEGER currentTickCount;
	LARGE_INTEGER previousTickCount;
	__int64 ticksPerSecond; // PC's tick rate
	const float TICK_RATE; 
	const float TIME_SCALE = 1.0f;
	const double MAX_ACCUMULATED_TIME = 1.0f / 15.0f;

};