#pragma once
#include "GameState.h"
#include "TextureManager.h";
class PauseState : public GameState
{
public:
	PauseState(SDLApplication* g, TextureManager* TM);

	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents(SDL_Event& event) {};
};

