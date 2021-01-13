#include "PauseState.h"

PauseState::PauseState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm)
{
	LoadButtons();
}

void PauseState::update()
{
	GameState::update();
}

void PauseState::render()
{
	GameState::render();
}

bool PauseState::handleEvents(SDL_Event& event)
{
	return GameState::handleEvents(event);
}

void PauseState::LoadButtons()
{
	Texture* tMain = tM->getTexture(mainButton); //Guardamos la textura

//Para que aparezca en mitad de pantalla
	int POS_HEIGHT = OFFSET_HEIGHT / 2 - (tMain->getH() / 2);
	int POS_WIDTH = OFFSET_WIDTH / 2 - (tMain->getW() / 6);

	Point2D posMain = Point2D(POS_WIDTH, POS_HEIGHT);

	//Botón
	MenuButton* newButMain = new MenuButton(posMain, g, tMain, tMain->getW() / 3, tMain->getH(), MainM);
	gO.push_back(newButMain);
	events.push_back(newButMain);

	Texture* tExit = tM->getTexture(exitButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	POS_HEIGHT = OFFSET_HEIGHT / 4 - (tExit->getH() / 2);
	POS_WIDTH = OFFSET_WIDTH / 2 - (tExit->getW() / 6);

	Point2D posExit = Point2D(POS_WIDTH, POS_HEIGHT);

	//Botón
	MenuButton* newButExit = new MenuButton(posExit, g, tExit, tExit->getW() / 3, tExit->getH(), Exit);
	gO.push_back(newButExit);
	events.push_back(newButExit);

	Texture* tSave = tM->getTexture(saveButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	POS_HEIGHT = OFFSET_HEIGHT / 8 - (tSave->getH() / 2);
	POS_WIDTH = OFFSET_WIDTH / 2 - (tSave->getW() / 6);

	Point2D posSave = Point2D(POS_WIDTH, POS_HEIGHT);

	//Botón
	MenuButton* newButSave = new MenuButton(posSave, g, tSave, tSave->getW() / 3, tSave->getH(), Save);
	gO.push_back(newButSave);
	events.push_back(newButSave);


	Texture* tResume = tM->getTexture(resumeButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	POS_HEIGHT = (OFFSET_HEIGHT - OFFSET_HEIGHT/4) - (tSave->getH() / 2);
	POS_WIDTH = OFFSET_WIDTH / 2 - (tSave->getW() / 6);

	Point2D posResume = Point2D(POS_WIDTH, POS_HEIGHT);

	//Botón
	MenuButton* newButResume = new MenuButton(posResume, g, tResume, tResume->getW() / 3, tResume->getH(), Resume);
	gO.push_back(newButResume);
	events.push_back(newButResume);
}

void PauseState::Save(SDLApplication* game)
{
	game->SaveGame();
}

void PauseState::MainM(SDLApplication* game)
{
	game->ChangeState(Menu);
}

void PauseState::Exit(SDLApplication* game)
{
	game->Salir();
}

void PauseState::Resume(SDLApplication* game) {
	game->ResumeGame();
}
