#include "RenderComponent.h"
#include "MovementMessage.h"
#include "RenderManager.h"

RenderComponent::RenderComponent() :
	sprite(nullptr),
	renderMode(RenderMode::Scaled)
{
}

RenderComponent::~RenderComponent()
{
	if (sprite)
	{
		RenderEngine::GetInstance().UnloadSprite(sprite);
	}
}

void RenderComponent::Tick(float deltaTime)
{
}

void RenderComponent::ReceiveMessage(Message* message)
{

}
