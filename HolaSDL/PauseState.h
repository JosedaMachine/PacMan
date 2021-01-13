#pragma once
#include "GameState.h"
#include "TextureManager.h";
#include "MenuButton.h";

class PauseState : public GameState
{
public:
	PauseState(SDLApplication* g, TextureManager* TM);

	virtual void update();
	virtual void render();
	virtual bool handleEvents(SDL_Event& event);

	void LoadButtons();

private:
	static void MainM(SDLApplication* game);
	static void Exit(SDLApplication* game);
	static void Save(SDLApplication* game);
};

