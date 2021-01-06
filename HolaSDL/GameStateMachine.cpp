#include "GameStateMachine.h"

GameState GameStateMachine::currentState()
{
    return (*states.top());
}


void GameStateMachine::changeState(GameState state)
{
    GameState* estado = &state;

    popState();
    pushState(estado);
}

void GameStateMachine::pushState(GameState* state)
{
    states.push(state);
}

void GameStateMachine::popState()
{
    states.pop();
}
