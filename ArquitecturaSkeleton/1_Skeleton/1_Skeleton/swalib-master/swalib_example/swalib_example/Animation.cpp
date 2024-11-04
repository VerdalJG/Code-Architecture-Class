#include "Animation.h"
#include "Sprite.h"

Animation::Animation(std::string name, AnimationMode mode, bool isLooping, float fps)
{
    this->name = name;
	this->fps = fps;
	this->isLooping = isLooping;
    this->mode = mode;
}

void Animation::Update(float deltaTime)
{
    if (mode == AnimationMode::Individual && animationFrames.empty())
    {
        return;
    }

    elapsedTime += deltaTime;
    float frameTime = 1.0f / fps;

    // Check if it's time to move to the next frame
    while (elapsedTime >= frameTime) 
    {
        elapsedTime -= frameTime;
        AdvanceFrame();
    }
}

void Animation::AdvanceFrame()
{
    if (mode == AnimationMode::Individual)
    {
        if (currentFrameIndex + 1 < animationFrames.size())
        {
            ++currentFrameIndex;
        }
        else if (isLooping)
        {
            currentFrameIndex = 0;
        }
    }
    else if (mode == AnimationMode::SpriteSheet)
    {
        vec2 grid = spriteSheet->GetSpriteSheetLayout();
        int numSprites = static_cast<int>(grid.x) * static_cast<int>(grid.y);

        if (currentFrameIndex + 1 < numSprites)
        {
            ++currentFrameIndex;
        }
        else if (isLooping)
        {
            currentFrameIndex = 0;
        }
    }
}

void Animation::Reset()
{
    currentFrameIndex = 0; 
    elapsedTime = 0.0f;
}

Sprite* Animation::GetCurrentFrame() const
{
    return animationFrames.empty() ? nullptr : animationFrames[currentFrameIndex];
}
