#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "texture.h";
class MenuButton :
    public EventHandler, GameObject
{
	Texture* t;

public:
	MenuButton(Point2D pos, int w, int h, Texture* te);
	virtual void render();
};

