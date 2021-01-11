#include "EndState.h"

void EndState :: render() {
	GameState::render();
}

EndState::EndState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm)
{
	load();
}

void EndState::load() {
	Point2D pos = Point2D(POS_WIDTH, POS_HEIGHT);


	MenuButton* newBut = new MenuButton(pos, g.get);
}
