#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	Texture* bG;
	Texture* title;
	MainMenuState(SDLApplication* game, TextureManager* tM);


	static void play(SDLApplication* game);
	static void Load(SDLApplication* game);

	virtual void render();

	void renderTitleNBg();

	

	//Como estamos llamando al handleEvent de GameState, no hace falta tener esto
	//virtual bool handleEvents(SDL_Event& event);
};

