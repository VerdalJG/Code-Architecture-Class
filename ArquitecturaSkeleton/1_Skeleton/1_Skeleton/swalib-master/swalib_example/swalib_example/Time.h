#pragma once
#include <Windows.h>

unsigned int GetTime()
{
	LARGE_INTEGER lCounter;
	LARGE_INTEGER lFrequency;
	QueryPerformanceCounter(&lCounter);
	QueryPerformanceFrequency(&lFrequency);
	return 0;
	//QueryPerformanceFrequency(&lInt);
}

