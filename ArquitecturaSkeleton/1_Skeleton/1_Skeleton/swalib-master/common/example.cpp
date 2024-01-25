#include "../swalib_example/swalib_example/GameLogic.h"
#include "../swalib_example/swalib_example/Render.h"
#include "../swalib_example/swalib_example/Time.h"

void Init();
//void Update();
void ShutDown();

int Main(void)
{
	Init();

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		currentTime = GetTime(); // Get timestamp of current frame
		elapsed = currentTime - previousTime; // Calculate time elapsed from previous frame to this frame
		previousTime = currentTime; // Record a timestamp of current frame

		accumulatedTime += elapsed;

		while (accumulatedTime >= frameRate) // When 0.017s passes
		{
			
			// Game Logic
			UpdateGame(frameRate);
			accumulatedTime -= frameRate; // Reset the 'wait' value
			
			if (accumulatedTime >= MAX_ACCUMULATED_TIME) accumulatedTime = 0;
		}
		UpdateTime();
		// Render
		Render();
		
	}

	// End app.
	ShutDown();

	return 0;
}

void Init()
{
	InitTime();
	InitGame();
	InitRender();
	SetLogicTime();
}

void ShutDown()
{
	// Unload textures.
	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texsmallball);
	FONT_End();
}