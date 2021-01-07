#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	MainMenuState()
	{

	}

	~MainMenuState()
	{

	}

	virtual void render(){};
	virtual void update(){};
	virtual void HandleEvents(SDL_Event& event){};

};

