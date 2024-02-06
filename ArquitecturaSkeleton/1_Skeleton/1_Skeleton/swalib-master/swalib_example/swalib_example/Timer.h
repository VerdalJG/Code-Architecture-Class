#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	void InitSlotsToProcess();
	bool ProcessSlots();
	double GetTime();

private:
	double FPS;
	double previousTime;
	double currentTime;
	double elapsed;
	double accumulatedTime;
	__int64 timestampStart;
	__int64 TickFrequency; // PC's tick rate
	const float LOGIC_TICK_RATE; // Cast first value or else the result is truncated -> you get 0
	const float TIME_SCALE = 1.f;
	const double MAX_ACCUMULATED_TIME = static_cast<double>(1) / 15;

};