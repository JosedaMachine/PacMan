#include "EndState.h"


EndState::EndState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm)
{
	load();
}

void EndState::load() {
	Texture* tMain = tM->getTexture(mainButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	POS_HEIGHT = OFFSET_HEIGHT / 2 - (tMain->getH() / 2);
	POS_WIDTH = OFFSET_WIDTH / 2  - (tMain->getW() / 6);

	Point2D posMain = Point2D(POS_WIDTH, POS_HEIGHT);

	//Bot�n
	MenuButton* newButMain = new MenuButton(posMain,g,tMain, tMain->getW()/3, tMain->getH(), MainM);
	gO.push_back(newButMain);
	events.push_back(newButMain);

	Texture* tExit = tM->getTexture(exitButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	POS_HEIGHT = OFFSET_HEIGHT / 4 - (tExit->getH() / 2);
	POS_WIDTH = OFFSET_WIDTH / 2 - (tExit->getW() / 6);

	Point2D posExit = Point2D(POS_WIDTH, POS_HEIGHT);

	//Bot�n
	MenuButton* newButExit = new MenuButton(posExit, g, tExit, tExit->getW() / 3, tExit->getH(), Exit);
	gO.push_back(newButExit);
	events.push_back(newButExit);
}

bool EndState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
	//player->handleEvents(key);
	//el handle event del player, sacar el menu y esas cosas

	return true;
}

void EndState::update()
{
	GameState::update();
}

void EndState::render() {
	GameState::render();
}

void EndState::MainM(SDLApplication* game)
{
	game->ChangeState(Menu);
}

void EndState::Exit(SDLApplication* game)
{
	game->Salir();
}