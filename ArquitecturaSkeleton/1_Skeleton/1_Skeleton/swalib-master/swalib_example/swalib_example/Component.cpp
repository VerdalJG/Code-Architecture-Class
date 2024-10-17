#include "Component.h"
#include "GameManager.h"
#include "WorldManager.h"


World* Component::GetWorld()
{
    return WorldManager::GetInstance().GetCurrentWorld();
}
