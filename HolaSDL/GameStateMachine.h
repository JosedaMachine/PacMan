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

	~GameStateMachine()
	{
		while (!states.empty())
			popState();
	}
};

