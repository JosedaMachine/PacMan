#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "texture.h";

class MenuButton :
    public GameObject, EventHandler
{
	Texture* t;

public:
	MenuButton(Point2D pos, Texture* te, int w, int h, float multiplier);
	virtual void render();
};

