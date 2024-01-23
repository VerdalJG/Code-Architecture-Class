#include "../swalib_example/swalib_example/GameUpdate.h"
#include "../swalib_example/swalib_example/Render.h"
#include "../swalib_example/swalib_example/Init.h"
#include "../swalib_example/swalib_example/Time.h"

void ShutDown();

void Update();

int Main(void)
{
	Init();

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		// Render
		Render();

		Update();

		SYS_Pump();	// Process Windows messages.
		SYS_Sleep(17);	// To force 60 fps
	}

	// End app.
	ShutDown();

	return 0;
}

void Update()
{
	// Game Logic
	GameLoop();
	GetTime();
}

void ShutDown()
{
	// Unload textures.
	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texsmallball);
	FONT_End();
}