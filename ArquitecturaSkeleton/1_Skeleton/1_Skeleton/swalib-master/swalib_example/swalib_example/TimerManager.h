#pragma once
#include <Windows.h>

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	bool ShouldTick();
	float GetFixedTickRate();
	void UpdateTime();
	double GetFPS() { return fps; }
	double GetTime();
	double GetLogicTime() { return logicTime; }
	

private:
	
	void HandleDeathSpiral();

	double fps;
	double deltaTime;
	double accumulatedTime;
	double logicTime;
	LARGE_INTEGER initialTickCount;
	LARGE_INTEGER currentTickCount;
	LARGE_INTEGER previousTickCount;
	__int64 ticksPerSecond; // PC's tick rate
	const float TICK_RATE = 1.0f / 60.0f;
	const float TIME_SCALE = 2.0f;
	const double MAX_ACCUMULATED_TIME = 1.0f / 15.0f;

};