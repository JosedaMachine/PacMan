#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "texture.h";
#include "SDLApplication.h";

using  CallBackOnClick = void(SDLApplication* g);

class MenuButton :
    public EventHandler, public GameObject
{
protected:
	CallBackOnClick* cbOnClick;
public:
	SDLApplication* g;
	Texture* t;
	MenuButton(Point2D pos, SDLApplication* g, Texture* te, int w, int h, CallBackOnClick* function);
	virtual void render();
	bool handleEvents(SDL_Event& event);
};

