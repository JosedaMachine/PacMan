#pragma once
#include "SDL.h"
class EventHandler
{
public:
	virtual bool handleEvents(SDL_Event& event) = 0;
};

