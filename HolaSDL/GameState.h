#pragma once
#include <list>;
#include "EventHandler.h";
#include "GameObject.h";
#include "TextureManager.h"
using namespace std;

class SDLApplication;

class GameState
{
public:
	list<EventHandler*> events;
	
	TextureManager* tM;
	list<GameObject*> gO;


	GameState(SDLApplication* game, TextureManager* textM);
	//este virtual va a hacer la cascada de los hijos. Es de padres a hijos, usando el virtual 
	virtual ~GameState();	
	
	virtual void render();
	virtual void update();
	//el HandlEvents si que va a ser distinto en cada uno de los estados 
	//Y POR ESO TIENE QUE SER VIRTUAL
	virtual bool handleEvents(SDL_Event& event);

protected:
	int OFFSET_WIDTH; //Tamaño de cada texturas en un mapa de casillas
	int OFFSET_HEIGHT;
	SDLApplication* g;

	

public:
	int getOffsetWidth() const { return OFFSET_WIDTH; }
	int getOffsetHeight() const { return OFFSET_HEIGHT; }
};

