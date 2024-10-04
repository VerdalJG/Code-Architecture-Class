#include "Timer.h"

TimeManager::TimeManager() :
	FPS(0),
	deltaTime(0),
	accumulatedTime(0),
	logicTime(0)
{
	// Initialize PC Frequency
	LARGE_INTEGER liFrequency;
	QueryPerformanceFrequency(&liFrequency);

	// Get the frequency of ticks of the PC per second
	ticksPerSecond = liFrequency.QuadPart;

	// Get initial tick count since the program started
	QueryPerformanceCounter(&initialTickCount);
	previousTickCount = initialTickCount;
	currentTickCount = initialTickCount;
}

TimeManager::~TimeManager()
{
}

float TimeManager::GetFixedTickRate()
{
	return TICK_RATE;
}

void TimeManager::HandleDeathSpiral()
{
	// Ensure accumulated time doesn't get out of hand so we dont get too many physics steps
	if (accumulatedTime >= MAX_ACCUMULATED_TIME)
	{
		accumulatedTime = MAX_ACCUMULATED_TIME;
	}
}


void TimeManager::UpdateTime()
{
	// Current timestamp
	QueryPerformanceCounter(&currentTickCount);

	// Get elapsed ticks
	UINT64 elapsedTicks = currentTickCount.QuadPart - previousTickCount.QuadPart;

	// Convert to microseconds to prevent losing precision due to floating point values (small number divided by big number)
	UINT64 elapsedTimeMicroSeconds = (elapsedTicks * 1000000) / ticksPerSecond;

	// Cast to double and convert back to seconds
	deltaTime = static_cast<double>(elapsedTimeMicroSeconds) / 1000000.0;

	// Accumulate time elapsed with timescale multiplier
	accumulatedTime += deltaTime * TIME_SCALE;

	HandleDeathSpiral();

	// Get framerate every frame
	FPS = 1 / deltaTime;

	// Record the current timestamp as the previous timestamp for the next frame
	previousTickCount = currentTickCount;
}

double TimeManager::GetTime()
{
	// Get total elapsed ticks
	UINT64 totalElapsedTicks = currentTickCount.QuadPart - initialTickCount.QuadPart;

	// Get current time in microseconds
	UINT64 currentTimeMicroSeconds = (totalElapsedTicks * 1000000) / ticksPerSecond;

	// Cast to double and convert back to seconds
	return static_cast<double>(currentTimeMicroSeconds) / 1000000.0;
}

bool TimeManager::ShouldTick()
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

