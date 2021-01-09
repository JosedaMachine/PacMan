#pragma once
#include <list>;
#include "EventHandler.h";
#include "GameObject.h";
#include "TextureManager.h"
using namespace std;

class Game;

class GameState
{
	list<EventHandler*> events;
public:
	Game* g;
	TextureManager* tM;
	list<GameObject*> gO;


	GameState(Game* game, TextureManager* textM);
	virtual void render();
	virtual void update();
	//el HandlEvents si que va a ser distinto en cada uno de los estados
	virtual void handleEvents(SDL_Event& event) {};

protected:
	int OFFSET_WIDTH; //Tamaño de cada texturas en un mapa de casillas
	int OFFSET_HEIGHT;

public:
	int getOffsetWidth() const { return OFFSET_WIDTH; }
	int getOffsetHeight() const { return OFFSET_HEIGHT; }
};

