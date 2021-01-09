#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	MainMenuState(Game* game, TextureManager* tM);

	~MainMenuState();

	virtual void render(){};
	virtual void update(){};
	virtual void HandleEvents(SDL_Event& event){};

};

