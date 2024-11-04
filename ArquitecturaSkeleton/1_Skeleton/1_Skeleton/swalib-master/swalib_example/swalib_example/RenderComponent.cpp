#include "RenderComponent.h"
#include "MovementMessage.h"
#include "RenderManager.h"
#include "Animation.h"

RenderComponent::RenderComponent() :
	currentSprite(nullptr),
	renderMode(RenderMode::Scaled)
{
}

RenderComponent::RenderComponent(RenderComponent& copy)
{
    SetSprite(copy.GetSprite());
    SetRenderMode(copy.GetRenderMode());
    SetPositionOffset(copy.GetPositionOffset());
    SetAllAnimations(copy.GetAllAnimations());
}

RenderComponent::~RenderComponent()
{
    for (Animation* animation : animations)
    {
        Sprite* sprite = animation->GetSpriteSheet();
        if (sprite)
        {
            RenderManager::GetInstance().UnloadSprite(sprite);
        }
        else
        {
            for (Sprite* animationFrame : animation->GetAnimationFrames())
            {
                RenderManager::GetInstance().UnloadSprite(animationFrame);
            }
        }
    }
}

void RenderComponent::Tick(float deltaTime)
{
    if (currentAnimation)
    {
        currentAnimation->Update(deltaTime);
        if (currentAnimation->GetAnimationMode() == AnimationMode::Individual)
        {
            currentSprite = currentAnimation->GetCurrentFrame(); // Fetch the current animation frame
        }
    }
}

void RenderComponent::ReceiveMessage(Message* message)
{

}

void RenderComponent::SetCurrentAnimation(std::string animationName)
{
    if (currentAnimation && currentAnimation->GetName() == animationName)
    {
        return;
    }
    for (Animation* animation : animations)
    {
        if (animation->GetName() == animationName)
        {
            currentAnimation = animation;
            currentAnimation->Reset();
        }
    }
}

Component* RenderComponent::Clone()
{
    RenderComponent* clone = new RenderComponent(*this); // Use copy constructor
    return clone;
}

void RenderComponent::AddAnimation(Animation* animation)
{
    // Only add animation if it is not registered
    auto iterator = std::find(animations.begin(), animations.end(), animation);

    if (iterator == animations.end())
    {
        animations.push_back(animation);
    }
}