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
	//DUDAS
	//Si GameState tiene un campo Game* g. Y PlayState hereda g, si desde un GameCharacter intento llamar a un metodo de Game, tengo que hacer un getter de PlayState que devuelva un getter de Game. Es correcto?

	//Es correcto tener en GameCharacter un puntero a PlayState? Y que Map , InfoBar,.. tengan los punteros correspondientes? Ya que en caso de los botones, hay 3 estados distintos en los que ellos existen
	Game g;

	try
	{
		//Carga de juego aqui por si ocurre un fallo al leer archivos, ya que el load se llamaba en la constructora
		//g.load(3);  //haremos el load dentro de propio Game. LLamando al PlayState
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