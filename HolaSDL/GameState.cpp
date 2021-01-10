#include "GameState.h"
#include "SDLApplication.h";

GameState::GameState(SDLApplication* game, TextureManager* textM)
{
	g = game;
	tM = textM;
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

