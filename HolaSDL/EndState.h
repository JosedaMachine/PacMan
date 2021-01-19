#pragma once
#include "GameState.h";
#include "TextureManager.h";
#include "MenuButton.h";
#include "SDLApplication.h";

//No se declara update y render porque no hay que hacer nada especial
//Y así se llama directamente al padre
class EndState : public GameState
{
	Texture* title;
	int POS_HEIGHT;
	int POS_WIDTH;

public:
	EndState(SDLApplication* g, TextureManager* Tm);

	void load();
	virtual bool handleEvents(SDL_Event& event);
	virtual void render();

	static void MainM(SDLApplication* game);
	static void Exit(SDLApplication* game);
private:
	void renderTitle();
};

