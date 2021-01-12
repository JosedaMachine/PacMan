#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "texture.h"
#include "GameObject.h"

//si pongo aqui el Include "Game.h" se genera dependencia circular,  por eso lo meto en el cpp

class PlayState; //engañar al Editor Texto. Ya no hace falta hacerlo con el Game ya que el Game ya no incluye al mapa
using namespace std;

//Tipos de celdas
enum  MapCell {Empty, Wall, Foodie, Vitamins};

class GameMap : public GameObject
{
	//friend class Game;
	friend class PlayState;
private:

	MapCell** celdas; //Array dinámico de 2D

public:
	PlayState* pS;
	GameMap(Point2D pos, int fils, int cols, PlayState* pSt);
	virtual ~GameMap();
	virtual void saveToFile(ofstream& output);
	void render();
	bool intersectWall(const SDL_Rect& rect) const;
};