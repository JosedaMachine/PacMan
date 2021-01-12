#include "MenuButton.h"

MenuButton::MenuButton(Point2D pos, Texture* te ,int w, int h, float multiplier) : GameObject(pos, w* multiplier, h*multiplier) {
	t = te;
}

void MenuButton::render() 
{
	SDL_Rect destRect = getDestRect();

	t->renderFrame(destRect, 0, 1);
}