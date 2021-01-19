#pragma once
#include "GameState.h"
#include "TextureManager.h";
#include "MenuButton.h";

class PauseState : public GameState
{
public:
	Texture* title;
	string inputText = "Some Text";
	
	PauseState(SDLApplication* g, TextureManager* TM);



	virtual void update();
	virtual void render();
	virtual bool handleEvents(SDL_Event& event);

	void LoadTitle();
	
	void LoadButtons();

	void LoadResumeButton();

	void LoadSaveButton();

	void LoadExitButton();

	void LoadMainButton();

private:
	static void MainM(SDLApplication* game);
	static void Exit(SDLApplication* game);
	static void Save(SDLApplication* game);
	static void Resume(SDLApplication* game);
};

