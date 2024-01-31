#pragma once
#include <Windows.h>
#include "GameManager.h"

class Timer
{
public:
	Timer();
	~Timer();

	void InitSlotsToProcess();
	void ProcessSlots();

private:
	const double MAX_ACCUMULATED_TIME = static_cast<double>(1) / 15;

	double previousTime;
	double currentTime;
	double elapsed;
	double accumulatedTime;
	__int64 timestampStart = 0;
	__int64 TickFrequency; // PC's tick rate
	const float frameRate = static_cast<float>(1) / 60; // Cast first value or else the result is truncated -> you get 0

};

void ProcessSlots()
{
	currentTime = GetTime(); // Get timestamp of current frame
	elapsed = currentTime - previousTime; // Calculate time elapsed from previous frame to this frame
	previousTime = currentTime; // Record a timestamp of current frame
}


/// <summary>
/// 
/// </summary>
/// <returns>Time in seconds since the start of the program</returns>
double GetTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return static_cast<double>(li.QuadPart - timestampStart) / TickFrequency;
}


// Call when you call to render
void UpdateFPS()
{
	// Increase frames by 1
	framesElapsed++;

	// Calculate FPS for every 5 frames
	if (framesElapsed % 5 == 1)
	{
		time1 = GetTime();
	}

	else if (framesElapsed % 5 == 0)
	{
		time1 = time2;
		time2 = GetTime();
		diffTime = fabs(time2 - time1);
	}

	FPS = 5 / diffTime;
}

