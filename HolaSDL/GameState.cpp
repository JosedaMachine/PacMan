#include "GameState.h"
#include "SDLApplication.h";

GameState::GameState(SDLApplication* game, TextureManager* textM)
{
	g = game;
	tM = textM;
	OFFSET_HEIGHT = g->getHeight();		//Para que los estados no tengan que pedirlo a SDLApplication
	OFFSET_WIDTH = g->getWidth();
}

GameState::~GameState()
{	//Borramos todos los elementos de la lista y vaciamos la lista
	for (GameObject* gameOb : gO) delete gameOb;	

	gO.clear();
}


void GameState::update()
{	//Update de todos los gameObjects
	for (GameObject* gameOb : gO)
		gameOb->update();
}

void GameState::render()
{	//Render de todos los gameObjects
	for (GameObject* o : gO) o->render();
}

bool GameState::handleEvents(SDL_Event& event) {
	for (EventHandler* h : events) if(h->handleEvents(event)) return true;

	return true;
}


