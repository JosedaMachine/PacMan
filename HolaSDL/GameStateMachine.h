#pragma once
#include "GameState.h"
#include <stack>

using namespace std;
class GameStateMachine
{
private:
	stack <GameState*> states;

	void pushState(GameState* state);
	void popState();

public:
	GameState currentState();
	void changeState(GameState state);
};

