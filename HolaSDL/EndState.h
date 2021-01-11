#pragma once
#include "GameState.h";
#include "TextureManager.h";
#include "MenuButton.h";
class EndState : public GameState
{
	int POS_HEIGHT = 50;
	int POS_WIDTH = 50;


public:
	EndState(SDLApplication* g, TextureManager* Tm);

	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents(SDL_Event& event) {};
	void load();
};

