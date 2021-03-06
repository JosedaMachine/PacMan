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
	SDL_Rect destRect;
	int multiplier = 5;

	destRect.w = title->getW() / 2;
	destRect.h = title->getH();
	destRect.x = OFFSET_WIDTH / 2 - destRect.w / 2;
	destRect.y = OFFSET_HEIGHT / 4 - destRect.h;
	title->renderFrame(destRect, 0, 0);

	GameState::render();
}

bool PauseState::handleEvents(SDL_Event& event)
{
	return GameState::handleEvents(event);
}

void PauseState::LoadButtons()
{
	//Cargamos cada m�todo por separado para que no sea tan largo
	LoadTitle();

	LoadMainButton();

	LoadExitButton();

	LoadSaveButton();

	LoadResumeButton();
}

void PauseState::LoadTitle()
{
	title = tM->getTexture(PauseButton);
}

void PauseState::LoadResumeButton()
{
	Texture* tResume = tM->getTexture(resumeButton); //Guardamos la textura

													 //Para que aparezca en mitad de pantalla
	int POS_HEIGHT = (OFFSET_HEIGHT / 2) - (tResume->getH() / 2);
	int POS_WIDTH = OFFSET_WIDTH / 2 - (tResume->getW() / 6);

	Point2D posResume = Point2D(POS_WIDTH, POS_HEIGHT);
	//Bot�n
	MenuButton* newButResume = new MenuButton(posResume, g, tResume, tResume->getW() / 3, tResume->getH(), Resume);
	gO.push_back(newButResume);
	events.push_back(newButResume);
}

void PauseState::LoadSaveButton()
{
	Texture* tSave = tM->getTexture(saveButton); //Guardamos la textura

												 //Para que aparezca en mitad de pantalla
	int POS_HEIGHT = OFFSET_HEIGHT / 3 - (tSave->getH() / 2);
	int POS_WIDTH = OFFSET_WIDTH / 2 - (tSave->getW() / 6);

	Point2D posSave = Point2D(POS_WIDTH, POS_HEIGHT);

	//Bot�n
	MenuButton* newButSave = new MenuButton(posSave, g, tSave, tSave->getW() / 3, tSave->getH(), Save);
	gO.push_back(newButSave);
	events.push_back(newButSave);
}

void PauseState::LoadExitButton()
{
	Texture* tExit = tM->getTexture(exitButton); //Guardamos la textura

												 //Para que aparezca en mitad de pantalla
	int POS_HEIGHT = OFFSET_HEIGHT / 1.2 - (tExit->getH() / 2);
	int POS_WIDTH = OFFSET_WIDTH / 2 - (tExit->getW() / 6);

	Point2D posExit = Point2D(POS_WIDTH, POS_HEIGHT);

	//Bot�n
	MenuButton* newButExit = new MenuButton(posExit, g, tExit, tExit->getW() / 3, tExit->getH(), Exit);
	gO.push_back(newButExit);
	events.push_back(newButExit);
}

void PauseState::LoadMainButton()
{
	Texture* tMain = tM->getTexture(mainButton); //Guardamos la textura

												 //Para que aparezca en mitad de pantalla
	int POS_HEIGHT = OFFSET_HEIGHT / 1.5 - (tMain->getH() / 2);
	int POS_WIDTH = OFFSET_WIDTH / 2 - (tMain->getW() / 6);

	Point2D posMain = Point2D(POS_WIDTH, POS_HEIGHT);

	//Bot�n
	MenuButton* newButMain = new MenuButton(posMain, g, tMain, tMain->getW() / 3, tMain->getH(), MainM);
	gO.push_back(newButMain);
	events.push_back(newButMain);
}

void PauseState::Save(SDLApplication* game)
{
	int code = game->askCodeNumber();
	game->SaveGame(code);
}

void PauseState::MainM(SDLApplication* game)
{
	game->MainM();
}

void PauseState::Exit(SDLApplication* game)
{
	game->Salir();
}

void PauseState::Resume(SDLApplication* game) {
	game->ResumeGame();
}
