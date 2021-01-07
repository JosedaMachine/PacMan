#include "GameStateMachine.h"

GameState* GameStateMachine::currentState()
{
    //Si no es vacia, pero no tendria porque dar fallo
    return states.top();
}

void GameStateMachine::pushState(GameState* state)
{
    states.push(state);
}

void GameStateMachine::changeState(GameState* state)
{
    popState();
    pushState(state);
}

void GameStateMachine::popState()
{
    if (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}
