#include "RenderComponent.h"
#include "MovementMessage.h"

RenderComponent::RenderComponent() :
	sprite(nullptr)
{
}

RenderComponent::~RenderComponent()
{
	if (sprite)
	{
		delete(sprite);
	}
}

void RenderComponent::Tick(float deltaTime)
{
}

void RenderComponent::ReceiveMessage(Message* message)
{

}
