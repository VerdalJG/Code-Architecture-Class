#include "../swalib_example/swalib_example/GameManager.h"
#include "../swalib_example/swalib_example/Render.h"
#include "../swalib_example/swalib_example/Timer.h"

int Main(void)
{
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