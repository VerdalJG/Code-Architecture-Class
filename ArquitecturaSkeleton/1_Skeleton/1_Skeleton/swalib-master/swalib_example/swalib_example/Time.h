#pragma once
#include <Windows.h>
#include "GameLogic.h"

void InitTime()
{
	// Initialize PC Frequency
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li)) printf("Frequency Query Failed!\n");

	PCFrequency = static_cast<double>(li.QuadPart) / 1000;
	

	// Record timestamp for when logic starts calculating 
	QueryPerformanceCounter(&li);
	startTime = static_cast<double>(li.QuadPart);

}

double GetTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return static_cast<double>(li.QuadPart - startTime)/PCFrequency;
}

void UpdateTime()
{
	// Increase frames by 1
	framesElapsed++;

	//
	if (framesElapsed % 5 == 1)
	{
		time1 = GetTime() / 1000;
	}

	else if (framesElapsed % 5 == 0)
	{
		time1 = time2;
		time2 = GetTime() / 1000;
		diffTime = fabs(time2 - time1);
	}

	FPS = 5 / diffTime;
}

