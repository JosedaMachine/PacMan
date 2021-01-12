#include "MenuButton.h"

MenuButton::MenuButton(Point2D pos, Texture* te ,int w, int h) : GameObject(pos, w, h) {
	t = te;
}

void MenuButton::render() 
{
	SDL_Rect destRect = getDestRect();

	t->renderFrame(destRect, 0, 1);
}