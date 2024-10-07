#include "Component.h"
#include "GameManager.h"

World* Component::GetWorld()
{
    return GameManager::GetInstance().world;
}
