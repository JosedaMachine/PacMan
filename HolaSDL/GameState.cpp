#include "GameState.h"
#include "Game.h";

void GameState::render()
{
	for (GameObject* o : gO) o->update();
}
