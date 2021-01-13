#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	Texture* title;
	MainMenuState(SDLApplication* game, TextureManager* tM);

	~MainMenuState();

	static void play(SDLApplication* game);

	virtual void render();
	virtual void update();

	void renderTitle();

	//Como estamos llamando al handleEvent de GameState, no hace falta tener esto
	//virtual bool handleEvents(SDL_Event& event);
};

