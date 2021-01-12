#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "texture.h";
#include "SDLApplication.h";

using  CallBackOnClick = void(SDLApplication* g);

class MenuButton :
    public GameObject, EventHandler
{
	Texture* t;
protected:
	CallBackOnClick* cbOnClick;
public:
	MenuButton(Point2D pos, Texture* te, int w, int h);
	virtual void render();
	bool handleEvents(SDL_Event& event);
};

