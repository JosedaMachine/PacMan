#pragma once
#include "GameState.h";
#include "TextureManager.h";
class EndState : public GameState
{
	EndState(SDLApplication* g, TextureManager* Tm) : GameState(g, Tm) {};
};

