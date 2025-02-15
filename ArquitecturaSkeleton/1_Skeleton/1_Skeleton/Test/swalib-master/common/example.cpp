#include "../swalib_example/swalib_example/GameManager.h"
#include "../swalib_example/swalib_example/Render.h"
#include "../swalib_example/swalib_example/Timer.h"

int Main(void)
{
	TimeManager* timer = new TimeManager();
	RenderEngine::GetInstance().Initialize(timer);
	GameManager::GetInstance().Initialize(timer);

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		GameManager::GetInstance().Slot();
		RenderEngine::GetInstance().Update();

		SYS_Pump();	// Process Windows messages.
		
	}

	// End app. Done in reverse order vs initialization
	GameManager::GetInstance().Terminate();
	RenderEngine::GetInstance().Terminate();

	return 0;
}