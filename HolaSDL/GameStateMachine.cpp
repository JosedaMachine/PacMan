#include "GameStateMachine.h"

GameState* GameStateMachine::currentState()
{
    //Si no es vacia, pero no tendria porque dar fallo
    return states.top();
}


void GameStateMachine::changeState(GameState* state)
{
    //GameState* estado = state;

    popState();
    pushState(state);
}

void GameStateMachine::pushState(GameState* state)
{
    states.push(state);
}

void GameStateMachine::popState()
{
    states.pop();
}
