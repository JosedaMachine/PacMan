#pragma once
#include "GameState.h"
#include "TextureManager.h";
class PauseState : public GameState
{
	PauseState(SDLApplication* g, TextureManager* TM);
};

