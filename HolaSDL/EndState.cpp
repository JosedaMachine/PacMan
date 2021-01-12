#include "EndState.h"


EndState::EndState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm)
{
	load();
}

void EndState::load() {
	POS_HEIGHT = OFFSET_HEIGHT / 2;
	POS_WIDTH = OFFSET_WIDTH / 2;

	Point2D pos = Point2D(POS_WIDTH, POS_HEIGHT);

	MenuButton* newBut = new MenuButton(pos, tM->getTexture(mainButton), tM->getTexture(mainButton)->getW()/3, tM->getTexture(mainButton)->getH());
	gO.push_back(newBut);
}

void EndState :: render() {
	GameState::render();
}