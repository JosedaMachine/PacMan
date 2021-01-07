#pragma once
#include <list>;
#include "EventHandler.h";
#include "GameObject.h";
using namespace std;

class Game;
enum TextureName { WallMap, Characters, Food, Digits, PowerUp };
class GameState
{
	list<GameObject*> gO;
	list<EventHandler*> events;
	Game* g;

public:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void HandleEvents() = 0;
};

