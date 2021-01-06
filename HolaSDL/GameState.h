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

protected:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void HandleEvents() = 0;
};

