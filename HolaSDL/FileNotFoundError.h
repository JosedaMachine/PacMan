#include "PacManError.h"
#pragma once
class FileNotFoundError : public PacManError
{
public:
	FileNotFoundError(const string s) : PacManError(s + ". Error de SDL") {};
};

