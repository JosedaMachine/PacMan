#include "GameState.h"
#include "Game.h";

GameState::GameState(Game* game, TextureManager* textM)
{
	g = game;
	tM = textM;

	g->render();
}

void GameState::update()
{
	for (GameObject* gameOb : gO)
		gameOb->update();
}

void GameState::render()
{
	for (GameObject* o : gO) o->update();
}

