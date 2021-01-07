#pragma once
#include <list>;
#include "EventHandler.h";
#include "GameObject.h";
using namespace std;

class Game;

class GameState
{
	list<GameObject*> gO;
	list<EventHandler*> events;
	Game* g;

public:

	GameState(Game* g) {};
	virtual void render();
	virtual void update() = 0;
	virtual void handleEvents(SDL_Event& event) = 0;
};

