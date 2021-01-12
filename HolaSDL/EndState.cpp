#include "EndState.h"


EndState::EndState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm)
{
	load();
}

void EndState::load() {
	Texture* t = tM->getTexture(mainButton); //Guardamos la textura

	//Para que aparezca en mitad de pantalla
	POS_HEIGHT = OFFSET_HEIGHT / 2 - (t->getH() / 2);
	POS_WIDTH = OFFSET_WIDTH / 2  - (t->getW() / 6);

	Point2D pos = Point2D(POS_WIDTH, POS_HEIGHT);

	//Botón
	MenuButton* newBut = new MenuButton(pos, t, t->getW()/3, t->getH(), 0.5);
	gO.push_back(newBut);
}

void EndState :: render() {
	GameState::render();
}