//Grupo 10
//Jose Daniel Rave Robayo
//Ángel López Benítez

#include "checkML.h"
#include <iostream>
#include <fstream>

#include "texture.h"
#include "Vector2D.h"
#include "Game.h"

using namespace std;

using uint = unsigned int;

void PacManGame() {

	//Por que PacMan y Ghisr han de llevar destructora si no crean nada?
	//El infobar tiene que heredar de GO?
	//SI pongo Game g = Game() lo hace por copia

	Game g;

	try
	{
		//Carga de juego aqui por si ocurre un fallo al leer archivos, ya que el load se llamaba en la constructora
		g.load(3);
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