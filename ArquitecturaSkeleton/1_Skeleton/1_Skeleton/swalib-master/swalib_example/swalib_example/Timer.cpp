#include "Timer.h"

void Timer::InitSlotsToProcess()
{
	// Initialize PC Frequency
	LARGE_INTEGER liStart, liFrequency;
	if (!QueryPerformanceFrequency(&liFrequency)) printf("Frequency Query Failed!\n");

	// Get the frequency of ticks of the PC per second
	TickFrequency = liFrequency.QuadPart;

	// Record timestamp for when logic starts calculating 
	QueryPerformanceCounter(&liStart);
	timestampStart = liStart.QuadPart; // Amount of ticks / frequency of ticks

}