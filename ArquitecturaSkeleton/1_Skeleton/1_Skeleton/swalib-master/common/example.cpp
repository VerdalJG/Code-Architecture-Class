#include "../swalib_example/swalib_example/GameLogic.h"
#include "../swalib_example/swalib_example/Render.h"
#include "../swalib_example/swalib_example/Time.h"

void Init();
void Update();
void ShutDown();

int Main(void)
{
	Init();

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{

		Update();
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
}

void Update()
{
	currentTime = GetTime(); // Get timestamp of current frame
	elapsed = currentTime - previousTime; // Calculate time elapsed from previous frame to this frame
	previousTime = currentTime; // Record a timestamp of current frame

	while (elapsed >= frameRate) // When 0.017s passes
	{
		UpdateTime();
		// Game Logic
		UpdateGame(elapsed);
		elapsed -= frameRate; // Reset the 'wait' value
		// Render
		Render();
		SYS_Pump();	// Process Windows messages.
		//SYS_Sleep(17);	// To force 60 fps
	}
	
}

void ShutDown()
{
	// Unload textures.
	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texsmallball);
	FONT_End();
}