#include "PacManError.h"
#pragma once
class FileFormatError : public PacManError
{
public:
	FileFormatError(const string s) :PacManError(s + ". Error de SDL") {};
};

