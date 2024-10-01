#include "Timer.h"

Timer::Timer() :
	FPS(0),
	deltaTime(0),
	accumulatedTime(0),
	TICK_RATE(1.0f / 60.0f),
	TIME_SCALE(1),
	MAX_ACCUMULATED_TIME(1.0f / 15.0f)
{
	// Initialize PC Frequency
	LARGE_INTEGER liFrequency;
	QueryPerformanceFrequency(&liFrequency);

	// Get the frequency of ticks of the PC per second
	ticksPerSecond = liFrequency.QuadPart;

	// Record timestamp for when logic starts calculating 
	QueryPerformanceCounter(&previousTickCount);
	currentTickCount = previousTickCount;
}

Timer::~Timer()
{
}

float Timer::GetFixedTickRate()
{
	return TICK_RATE;
}

void Timer::HandleDeathSpiral()
{
	// Accumulate time elapsed with timescale multiplier
	accumulatedTime += deltaTime * TIME_SCALE;

	// Ensure accumulated time doesn't get out of hand so we dont get too many physics steps
	if (accumulatedTime >= MAX_ACCUMULATED_TIME)
	{
		accumulatedTime = MAX_ACCUMULATED_TIME;
	}
}


void Timer::UpdateTime()
{
	// Current timestamp
	QueryPerformanceCounter(&currentTickCount);

	// Get elapsed ticks
	UINT64 elapsedTicks = currentTickCount.QuadPart - previousTickCount.QuadPart;

	// Convert to microseconds to prevent losing precision due to floating point values (small number divided by big number)
	UINT64 elapsedTimeMicroSeconds = (elapsedTicks * 1000000) / ticksPerSecond;

	// Cast to double and convert back to seconds
	deltaTime = static_cast<double>(elapsedTimeMicroSeconds) / 1000000.0;

	HandleDeathSpiral();

	// Get framerate every frame
	FPS = 1 / deltaTime;

	// Record the current timestamp as the previous timestamp for the next frame
	previousTickCount = currentTickCount;
}

double Timer::GetTime()
{
	// Get current time in microseconds
	UINT64 currentTimeMicroSeconds = (currentTickCount.QuadPart * 1000000) / ticksPerSecond;

	// Cast to double and convert back to seconds
	return static_cast<double>(currentTimeMicroSeconds) / 1000000.0;
}

bool Timer::ShouldTick()
{
	if (accumulatedTime >= TICK_RATE)
	{
		// Reset the 'wait' value
		accumulatedTime -= TICK_RATE;
		logicTime += TICK_RATE;
		return true;
	}
	else
	{
		return false;
	}
}

