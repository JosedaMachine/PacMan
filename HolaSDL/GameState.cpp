#include "GameState.h"
#include "SDLApplication.h";

GameState::GameState(SDLApplication* game, TextureManager* textM)
{
	g = game;
	tM = textM;
	OFFSET_HEIGHT = g->getHeight();
	OFFSET_WIDTH = g->getWidth();
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

void GameState::handleEvents(SDL_Event& event) {
	for(EventHandler* h : events) 
}

