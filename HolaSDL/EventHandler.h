#pragma once
#include "SDL.h"
class EventHandler
{
	//Clase abstracta (Interfaz)
public:
	virtual bool handleEvents(SDL_Event& event) = 0;
};

