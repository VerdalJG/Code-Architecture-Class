#pragma once
#include "Component.h"
#include "Globals.h"

class Sprite;
class Message;

enum class RenderMode 
{
	Tiled,  // Texture is tiled based on entity scale
	Scaled  // Texture is scaled without repetition
};

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent() override;
	virtual void Tick(float deltaTime) override;
	virtual void ReceiveMessage(Message* message) override;

private:
	Sprite* sprite; //Sprite for Render
	vec2 positionOffset;
	RenderMode renderMode;  // Store the render mode (tile or scale)

public:
	Sprite* GetTexture() const { return sprite; }
	void SetSprite(Sprite* newSprite) { sprite = newSprite; }

	vec2 GetPositionOffset() const { return positionOffset; }
	void SetPositionOffset(vec2 newOffset) { positionOffset = newOffset; }

	RenderMode GetRenderMode() const { return renderMode; }
	void SetRenderMode(RenderMode newRenderMode) { renderMode = newRenderMode; }
};

