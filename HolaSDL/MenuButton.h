#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "texture.h";
#include "SDLApplication.h";

using  CallBackOnClick = void(SDLApplication* game);

class MenuButton :
    public GameObject, EventHandler
{
	Texture* t;

public:
	MenuButton(Point2D pos, Texture* te, int w, int h);
	virtual void render();
	bool handleEvent(SDL_Event& event);
};

