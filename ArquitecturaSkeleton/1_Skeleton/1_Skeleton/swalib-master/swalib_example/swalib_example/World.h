#pragma once
#include "Globals.h"
#include "Actor.h"

class Entity;
//class Actor;
class Solid;
class Sprite;
class TimeManager; 
class Background;
class Widget;
class Player;

enum class MoveDirection
{
	None,
	Up,
	Down,
	Left,
	Right
};

enum class CollisionLayer
{
	Default,
	Player,
	Balls,
	Environment,
	Bullet,
	NumLayers // This helps track the total count
};

class World
{
public:
	World();
	void BeginPlay();
	void InitializeCollisionMatrix();
	void Terminate();
	void RegisterActor(Actor* actor);
	void RemoveActor(Actor* actor);
	bool ShouldCollide(CollisionLayer layer1, CollisionLayer layer2);

	void RegisterSolid(Solid* solid);
	void RemoveSolid(Solid* solid);

	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);

	void Tick(float deltaTime);
	void ProcessInputs();
	
	const float GRAVITY_SCALE = 2.0f;

private:
	std::vector<Solid*> solids;
	std::vector<Actor*> actors;
	std::vector<Actor*> actorsToAdd;
	std::vector<Entity*> entities;
	Background* background;
	Player* player = nullptr;
	MoveDirection lastPressedDirection = MoveDirection::None;
	// Define the matrix using a 2D array of booleans
	bool collisionMatrix[static_cast<int>(CollisionLayer::NumLayers)][static_cast<int>(CollisionLayer::NumLayers)];

public:
	std::vector<Entity*> GetEntities() { return entities; }
	void SetPlayer(Player* newPlayer) { player = newPlayer; }
	Background* GetBackground() { return background; }
	void SetBackground(Background* newBackground);

	MoveDirection GetLastDirection() { return lastPressedDirection; }
	void SetLastDirection(MoveDirection newDirection) { lastPressedDirection = newDirection; }

	template<typename T>
	T* FindActor()
	{
		for (Actor* actor : actors)
		{
			if (T* derivedActor = dynamic_cast<T*>(actor))
			{
				return derivedActor;
			}
		}
		return nullptr;
	}

	template<typename T>
	T* SpawnActor(Actor* actor, vec2 position, vec2 scale, std::string name)
	{
		static_assert(std::is_base_of<Actor, T>::value, "SpawnActor can only spawn types derived from Entity");

		T* newActor = new T();
		Actor* castedActor = dynamic_cast<Actor*>(newActor);

		for (Component* component : actor->GetAllComponents())
		{
			Component* clonedComponent = component->Clone();
			castedActor->AddComponent(clonedComponent);
		}

		castedActor->SetName(name); // In theory, we should add a number to make it searchable by name, as this will cause duplicates
		castedActor->SetWorldScale(scale);
		castedActor->SetWorldPosition(position);

		RegisterActor(castedActor);

		return newActor;
	}
};

