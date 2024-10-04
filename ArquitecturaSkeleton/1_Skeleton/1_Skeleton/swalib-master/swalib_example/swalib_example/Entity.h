#pragma once
#include "Globals.h"

class Sprite;
class World;

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Tick(float _deltaTime) {};

protected:

	void CreateSprite(const char* FilePath, bool ScreenWrapping, vec2 SpriteSize);
	World* GetWorld();

	vec2 position;
	vec2 scale;
	
public:
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 newPosition);

	vec2 GetScale() { return scale; }
	void SetScale(vec2 newScale) { scale = newScale; }

	Sprite* GetSprite() { return sprite; }

private:
	Sprite* sprite;


};

