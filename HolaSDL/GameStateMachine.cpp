#include "GameStateMachine.h"

GameState* GameStateMachine::currentState()
{
    //Si no es vacia, pero no tendria porque dar fallo
    return states.top();
}

void GameStateMachine::pushState(GameState* state)
{	//Se mete un estado
    states.push(state);
}

void GameStateMachine::changeState(GameState* state)
{	//Sacamos el estado actual y metemos el nuevo
    popState();
    pushState(state);
}

void GameStateMachine::popState()
{	//Si hay un estado lo sacamos
    if (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}
