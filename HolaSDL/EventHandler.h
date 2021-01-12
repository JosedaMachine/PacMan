#pragma once
class EventHandler
{
	virtual void HandleEvents(SDL_Event& event) = 0;
};

