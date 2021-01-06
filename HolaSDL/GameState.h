#pragma once
#include <list>;
#include "EventHandler.h";
#include "GameObject.h";
using namespace std;

class GameState
{
	list<GameObject*> gO;
	list<EventHandler*> events;

protected:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void HandleEvents() = 0;
};

