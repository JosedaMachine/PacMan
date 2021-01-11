#pragma once
#include "GameState.h";
#include "TextureManager.h";
class EndState : public GameState
{
public:
	EndState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm) {};

	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents(SDL_Event& event) {};
};

