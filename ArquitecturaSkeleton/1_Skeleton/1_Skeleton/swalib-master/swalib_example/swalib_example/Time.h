#pragma once
#include <Windows.h>
#include "GameLogic.h"

double GetTime();

void InitTime()
{
	// Initialize PC Frequency
	LARGE_INTEGER liStart, liFrequency;
	if (!QueryPerformanceFrequency(&liFrequency)) printf("Frequency Query Failed!\n");

	// Get the frequency of ticks of the PC per second
	TickFrequency = liFrequency.QuadPart;

	// Record timestamp for when logic starts calculating 
	QueryPerformanceCounter(&liStart);
	timestampStart = liStart.QuadPart; // Amount of ticks / frequency of ticks
	previousTime = GetTime();
}

void SetLogicTime()
{
	logicStartTime = GetTime();
}

/// <summary>
/// 
/// </summary>
/// <returns>Time in seconds</returns>
double GetTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return static_cast<double>(li.QuadPart - timestampStart) / TickFrequency;
}


// Call when you call to render
void UpdateTime()
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

