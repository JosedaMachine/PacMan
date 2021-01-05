#include "PacManError.h"
#pragma once
class SDLError : public PacManError
{
public:
	SDLError(const string s) : PacManError(s + ". Error de SDL") {};
};

