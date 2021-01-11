#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "texture.h";
class MenuButton :
    public EventHandler, GameObject
{
	Texture* t;

	MenuButton(Point2D pos, int w, int h, Texture* te, Point2D siz);
	virtual void render();
};

