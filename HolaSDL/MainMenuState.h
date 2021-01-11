#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	MainMenuState(SDLApplication* game, TextureManager* tM);

	~MainMenuState();

	virtual void render(){};
	virtual void update(){};
	virtual void handleEvents(SDL_Event& event){};
};

