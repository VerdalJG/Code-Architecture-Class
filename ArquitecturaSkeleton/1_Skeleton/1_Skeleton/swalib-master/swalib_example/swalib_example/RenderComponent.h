#pragma once
#include "Component.h"
#include "Globals.h"

class Sprite;
class Message;
class Animation;

enum class RenderMode 
{
	Tiled,  // Texture is tiled based on entity scale
	Scaled  // Texture is scaled without repetition
};

class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(RenderComponent& copy);
	~RenderComponent() override;
	virtual void Tick(float deltaTime) override;
	virtual void ReceiveMessage(Message* message) override;
	void AddAnimation(Animation* animation);

private:
	Sprite* currentSprite; //Sprite for Render
	vec2 positionOffset;
	RenderMode renderMode;  // Store the render type (tile or scale)

	Animation* currentAnimation = nullptr;
	std::vector<Animation*> animations;

public:
	Sprite* GetSprite() const { return currentSprite; }
	void SetSprite(Sprite* newSprite) { currentSprite = newSprite; }

	Animation* GetCurrentAnimation() const { return currentAnimation; }
	void SetCurrentAnimation(std::string animationName);

	std::vector<Animation*> GetAllAnimations() { return animations; }
	void SetAllAnimations(std::vector<Animation*> newAnimations) { animations = newAnimations; }

	vec2 GetPositionOffset() const { return positionOffset; }
	void SetPositionOffset(vec2 newOffset) { positionOffset = newOffset; }

	RenderMode GetRenderMode() const { return renderMode; }
	void SetRenderMode(RenderMode newRenderMode) { renderMode = newRenderMode; }

	virtual Component* Clone() override;
};

