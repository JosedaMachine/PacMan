#include "MenuButton.h"

MenuButton::MenuButton(Point2D pos, SDLApplication* ga, Texture* te ,int w, int h, CallBackOnClick* function) : GameObject(pos, w, h) {
	t = te;
	g = ga;
	cbOnClick = function;
	textureFrame = 1;
}

void MenuButton::render() 
{
	SDL_Rect destRect = getDestRect();

	t->renderFrame(destRect, 0, textureFrame);
}

bool MenuButton::handleEvents(SDL_Event& event)
{
	SDL_Rect r = getDestRect();
	SDL_Point p = SDL_Point();

	SDL_GetMouseState(&p.x, &p.y);

	if (SDL_PointInRect(&p, &r) == SDL_TRUE)
	{
		textureFrame = 0;

		if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
		{
			cbOnClick(g);
			return true;
		}
	}
	else textureFrame = 1;

	return false;
}
