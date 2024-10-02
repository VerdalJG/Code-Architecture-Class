#pragma once
class Sprite;

class Entity
{
public:
	Entity();

protected:
	void SetSprite(Sprite* NewSprite) { Sprite = NewSprite; };

private:
	~Entity();
	Sprite* Sprite;
	
};

