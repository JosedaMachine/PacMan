#pragma once
#include "GameState.h"
#include <stack>

using namespace std;
class GameStateMachine
{
private:
	stack <GameState*> states;
public:
	void popState();
	GameState* currentState();
	void pushState(GameState* state);
	void changeState(GameState* state);

	GameStateMachine(){};

	//Cuando se destruye la máquina de estados, saca todos los estados, que se van destruyendo ellos solos
	~GameStateMachine()
	{
		while (!states.empty())
			popState();
	}
};

