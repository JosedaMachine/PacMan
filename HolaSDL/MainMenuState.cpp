#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* game, TextureManager* tM) : GameState(game, tM)
{
	Texture* t = tM->getTexture(playButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	int multiplier = 2;
	Point2D pos = Point2D(OFFSET_WIDTH / 2 - (t->getW()/ (6* multiplier)) , OFFSET_HEIGHT / 2 - (t->getH() / multiplier));

	//Botón
	MenuButton* newBut = new MenuButton(pos, t, t->getW()/(3* multiplier), t->getH()/ multiplier);
	gO.push_back(newBut);
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

