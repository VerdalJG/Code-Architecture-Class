#pragma once
#include "Globals.h"

class Sprite;

enum class AnimationMode
{
    Individual,
    SpriteSheet
};

class Animation
{
public:
    using OnAnimationEndCallback = void (*)();
    Animation(std::string name, AnimationMode mode, bool isLooping = true, float fps = 5.0f);
    void Update(float deltaTime);
    void AdvanceFrame();

private:
    // Animation identifier and frames
    std::string name;
    std::vector<Sprite*> animationFrames; // Used in Individual type
    Sprite* spriteSheet = nullptr; // Used in SpriteSheet type

    // Animation data and type
    float fps;
    bool isLooping;
    AnimationMode mode;

    // Time control properties
    int currentFrameIndex = 0;
    float elapsedTime = 0.0f;
    OnAnimationEndCallback onAnimationEnd;

public:
    std::string GetName() { return name; }
    AnimationMode GetAnimationMode() { return mode; }
    Sprite* GetSpriteSheet() { return spriteSheet; }
    std::vector<Sprite*> GetAnimationFrames() { return animationFrames; }


    void SetLooping(bool isLooping) { this->isLooping = isLooping; }
    void SetFPS(float fps) { this->fps = fps; }
    void SetAnimationMode(AnimationMode mode) { this->mode = mode; }
    void SetOnAnimationEnd(OnAnimationEndCallback callback) { onAnimationEnd = callback; }

    void Reset();
    
    void AddFrame(Sprite* frame) { animationFrames.push_back(frame); }
    void SetSpriteSheet(Sprite* sprite) { this->spriteSheet = sprite; }

    // Get the current currentSprite to render - Only on individual mode
    Sprite* GetCurrentFrame() const;
    int GetCurrentFrameNumber() const { return currentFrameIndex; }
};