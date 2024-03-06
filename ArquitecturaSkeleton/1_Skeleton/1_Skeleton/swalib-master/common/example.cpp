#include "../swalib_example/swalib_example/GameManager.h"
#include "../swalib_example/swalib_example/Render.h"
#include "../swalib_example/swalib_example/Timer.h"

void Init();
void ShutDown();

int Main(void)
{
	Init();
	Renderer::GetInstance().Initialize();
	GameManager::GetInstance().Initialize();

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		GameManager::GetInstance().Slot();
		Renderer::GetInstance().Slot();

		SYS_Pump();	// Process Windows messages.
		
	}

	// End app. Done in reverse order vs initialization
	GameManager::GetInstance().Terminate();
	Renderer::GetInstance().Terminate();


	return 0;
}

//void Init()
//{
//	InitTime();
//	InitGame();
//	InitRender();
//}

//void ShutDown()
//{
//	// Unload textures.
//	CORE_UnloadPNG(texbkg);
//	CORE_UnloadPNG(texsmallball);
//	FONT_End();
//}



//currentTime = GetTime(); // Get timestamp of current frame
		//elapsed = currentTime - previousTime; // Calculate time elapsed from previous frame to this frame
		//previousTime = currentTime; // Record a timestamp of current frame

		//accumulatedTime += elapsed * TIME_SCALE;

		//if (accumulatedTime >= MAX_ACCUMULATED_TIME)
		//{
		//	accumulatedTime = MAX_ACCUMULATED_TIME;
		//}

		//while (accumulatedTime >= frameRate) // When 0.017s passes
		//{
		//	// Advance logic timer
		//	logicTime += frameRate;

		//	// Game Logic
		//	UpdateGame(frameRate);

		//	// Reset the 'wait' value
		//	accumulatedTime -= frameRate; 

		//	//SYS_Sleep(17); // To force 60 fps
		//}

		//UpdateFPS();
		//// Render
		//Render();
		//SYS_Pump(); // Process Windows messages.
		//SYS_Sleep(17); // To force 60 fps