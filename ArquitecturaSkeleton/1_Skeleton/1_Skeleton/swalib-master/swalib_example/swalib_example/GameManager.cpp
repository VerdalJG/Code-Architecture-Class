#include "GameManager.h"

GameManager* GameManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameManager;
	}
	else
	{
		return _instance;
	}
}

void GameManager::LogicSlot(float deltaTime)
{


}
