#pragma once
#include "Globals.h"

class Sprite;

class Entity
{
public:
	Entity();
	virtual void Tick(float _deltaTime) {};

protected:
	~Entity();
	void CreateSprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize);

	vec2 Position;
	vec2 Scale;
	
public:
	vec2 GetPosition() { return Position; }
	void SetPosition(vec2 NewPosition);

	vec2 GetScale() { return Scale; }
	void SetScale(vec2 NewScale) { Scale = NewScale; }

	Sprite* GetSprite() { return MySprite; }

private:
	Sprite* MySprite;


};

