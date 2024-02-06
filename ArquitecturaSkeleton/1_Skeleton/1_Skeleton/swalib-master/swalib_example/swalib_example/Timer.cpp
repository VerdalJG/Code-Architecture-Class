#include "Timer.h"

Timer::Timer() :
	previousTime(0),
	currentTime(0),
	elapsed(0),
	accumulatedTime(0),
	LOGIC_TICK_RATE(static_cast<float>(1) / 60),
	TIME_SCALE(1),
	MAX_ACCUMULATED_TIME(static_cast<double>(1) / 15)
{
	// Initialize PC Frequency
	LARGE_INTEGER liStart, liFrequency;
	QueryPerformanceFrequency(&liFrequency);

	// Get the frequency of ticks of the PC per second
	TickFrequency = liFrequency.QuadPart;

	// Record timestamp for when logic starts calculating 
	QueryPerformanceCounter(&liStart);
	timestampStart = liStart.QuadPart; // Amount of ticks / frequency of ticks
}

Timer::~Timer()
{
}

void Timer::InitSlotsToProcess()
{
	// Get timestamp of current frame
	currentTime = GetTime();

	// Calculate time elapsed from previous frame to this frame
	elapsed = currentTime - previousTime;

	// Record a timestamp of current frame
	previousTime = currentTime;

	// Get framerate every frame
	FPS = 1 / elapsed;

	// Accumulate time elapsed with timescale multiplier
	accumulatedTime += elapsed * TIME_SCALE;

	// Ensure accumulated time doesn't get out of hand so we dont get too many physics steps
	if (accumulatedTime >= MAX_ACCUMULATED_TIME)
	{
		accumulatedTime = MAX_ACCUMULATED_TIME;
	}
}

bool Timer::ProcessSlots()
{
	if (accumulatedTime >= frameRate)
	{
		// Reset the 'wait' value
		accumulatedTime -= frameRate;
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// 
/// </summary>
/// <returns>Time in seconds since the start of the program</returns>
double Timer::GetTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return static_cast<double>(li.QuadPart - timestampStart) / TickFrequency;
}


//void UpdateFPS()
//{
	// THE CODE BELOW DOES THE SAME THING BUT EVERY 5 FRAMES
	//// Increase frames by 1
	//framesElapsed++;
	//// Calculate FPS for every 5 frames
	//if (framesElapsed % 5 == 1)
	//{
	//	time1 = GetTime();
	//}
	//else if (framesElapsed % 5 == 0)
	//{
	//	time1 = time2;
	//	time2 = GetTime();
	//	diffTime = fabs(time2 - time1);
	//}
	//FPS = 5 / diffTime;
//}