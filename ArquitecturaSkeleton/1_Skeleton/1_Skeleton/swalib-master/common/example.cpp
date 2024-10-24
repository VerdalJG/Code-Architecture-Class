#include "../swalib_example/swalib_example/GameManager.h"
#include "../swalib_example/swalib_example/RenderManager.h"
#include "../swalib_example/swalib_example/TimerManager.h"
#include "../swalib_example//swalib_example/WorldManager.h"
#include "../swalib_example//swalib_example/InputManager.h"

int Main(void)
{
	TimeManager* timer = new TimeManager();
	RenderEngine::GetInstance().Initialize(timer);
	WorldManager::GetInstance().Initialize();
	InputManager::GetInstance().Initialize();
	GameManager::GetInstance().Initialize(timer);

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		InputManager::GetInstance().UpdateInput(); // Poll inputs at uncapped FPS
		GameManager::GetInstance().Slot();
		RenderEngine::GetInstance().Update();

		SYS_Pump();	// Process Windows messages.
	}

	// End app. Done in reverse order vs initialization
	GameManager::GetInstance().Terminate();
	WorldManager::GetInstance().Terminate();
	RenderEngine::GetInstance().Terminate();

	return 0;
}