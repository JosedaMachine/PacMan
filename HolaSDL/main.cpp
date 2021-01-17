//Grupo 10
//Jose Daniel Rave Robayo
//Ángel López Benítez

#include "checkML.h"
#include <iostream>
#include <fstream>

#include "texture.h"
#include "Vector2D.h"
#include "SDLApplication.h"

using namespace std;

using uint = unsigned int;

void PacManGame() {
	SDLApplication g;
	//menu
	try
	{
		g.run();
	}
	catch (PacManError& e)
	{
		cout << e.what();
	}
}

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	PacManGame();
	return 0;
}