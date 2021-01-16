#include "GameState.h"
#include "SDLApplication.h";

GameState::GameState(SDLApplication* game, TextureManager* textM)
{
	g = game;
	tM = textM;
	OFFSET_HEIGHT = g->getHeight();
	OFFSET_WIDTH = g->getWidth();
}

GameState::~GameState()
{
	for (GameObject* gameOb : gO) delete gameOb;

	gO.clear();
}


void GameState::update()
{
	for (GameObject* gameOb : gO)
		gameOb->update();
}

void GameState::render()
{
	for (GameObject* o : gO) o->render();
}

bool GameState::handleEvents(SDL_Event& event) {
	for (EventHandler* h : events) if(h->handleEvents(event)) return true;

	return true;
}


