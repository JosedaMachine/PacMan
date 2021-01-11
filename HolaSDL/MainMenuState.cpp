#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* game, TextureManager* tM) : GameState(game, tM)
{

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::render()
{
	GameState::render();
}

void MainMenuState::update()
{
	GameState::update();
}

