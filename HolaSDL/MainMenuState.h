#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	MainMenuState(SDLApplication* game, TextureManager* tM);

	~MainMenuState();

	static void play(SDLApplication* game);

	virtual void render();
	virtual void update();
	virtual bool handleEvents(SDL_Event& event);
};

