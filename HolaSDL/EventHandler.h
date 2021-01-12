#pragma once
class EventHandler
{
public:

	virtual void HandleEvents(SDL_Event& event) = 0;
};

