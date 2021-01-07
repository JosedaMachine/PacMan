#pragma once
#include <list>;
#include "EventHandler.h";
#include "GameObject.h";
using namespace std;

class Game;

class GameState
{
	list<EventHandler*> events;
public:
	Game* g;
	list<GameObject*> gO;
	int OFFSET_WIDTH; //Tamaño de cada texturas
	int OFFSET_HEIGHT;
	GameState(Game* g) {};
	virtual void render();
	virtual void update() = 0;
	virtual void handleEvents(SDL_Event& event) {};
};

