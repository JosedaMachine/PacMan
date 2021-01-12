#pragma once
#include "GameState.h";
#include "TextureManager.h";
#include "MenuButton.h";
#include "SDLApplication.h";

class EndState : public GameState
{
	int POS_HEIGHT;
	int POS_WIDTH;


public:
	EndState(SDLApplication* g, TextureManager* Tm);

	void load();

	virtual void update();
	virtual void render();
	virtual bool handleEvents(SDL_Event& event);

	static void MainM(SDLApplication* game);
	static void Exit(SDLApplication* game);
private:
};

