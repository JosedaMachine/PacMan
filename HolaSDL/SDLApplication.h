#pragma once
#include <fstream>
#include <array>
#include <string>

#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"

#include "GameMap.h"
#include "texture.h"
#include "PacMan.h"
#include "Ghost.h"
#include "SmartGhost.h"
#include "Vector2D.h"
#include "InfoBar.h"
#include "checkML.h"

#include "GameStateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "TextureManager.h"
#include "PauseState.h"
#include "EndState.h"

//Tiempo de refresco del juego
const int FRAME_RATE = 5;
//Tama�o en X e Y de la pantalla
const uint WIN_WIDTH = 700;
const uint WIN_HEIGHT = 700;

enum States {Menu, Play, Pause, End};

class SDLApplication
{
private:
	SDL_Window* window = nullptr; //Puntero a la ventana
	SDL_Renderer* renderer = nullptr;  //puntero a renderer

	GameStateMachine* stateMachine;
	TextureManager* tM;

	bool exit, hasWon; //Controladores del juego
public:
	SDLApplication();
	~SDLApplication();

	void run();
	void ChangeState(States s);
	void render();
	void handleEvent(SDL_Event& event, bool& exit);
	void Salir() { exit = true; }
	void Won() { hasWon = true; }
	void PauseGame();
	void ResumeGame();
	void MainM();
	void SaveGame(int codeNumber);
	void LoadGame(int codeNumber);
	int askCodeNumber();

	#pragma region GETTERS
	bool getHasWon() const { return hasWon; }
	int getWidth() const { return WIN_WIDTH; }
	int getHeight() const { return WIN_HEIGHT; }
	int getFrameRate() const { return FRAME_RATE; }
	#pragma endregion
};