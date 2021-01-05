#include <iostream>

#pragma once
using namespace std;
class PacManError: public logic_error
{
protected:
	PacManError(string message) :logic_error(message) {};
public:
};

