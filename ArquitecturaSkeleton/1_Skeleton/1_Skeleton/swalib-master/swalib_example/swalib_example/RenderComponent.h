#pragma once
#include "Component.h"
#include "Globals.h"

class Sprite;
class Message;

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
	vec2 finalPosition;

public:

	Sprite* GetSprite() { return sprite; }
	void SetSprite(Sprite* newSprite) { sprite = newSprite; }

	vec2 GetPositionOffset() { return positionOffset; }
	void SetPositionOffset(vec2 newOffset) { positionOffset = newOffset; }
};

