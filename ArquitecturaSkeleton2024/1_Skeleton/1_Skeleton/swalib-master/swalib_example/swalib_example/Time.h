#pragma once
#include <Windows.h>

unsigned int GetTime()
{
	LARGE_INTEGER lInt;
	QueryPerformanceCounter(&lInt);
	QueryPerformanceFrequency(&lInt);
	printf("hi");
	return 0;
	QueryPerformanceFrequency(&lInt);
}

