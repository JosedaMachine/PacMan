#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "texture.h"
#include "GameObject.h"

//si pongo aqui el Include "Game.h" se genera dependencia circular,  por eso lo meto en el cpp

class Game; //engañar al Editor Texto
using namespace std;

//Tipos de celdas
enum  MapCell {Empty, Wall, Foodie, Vitamins};

class GameMap : public GameObject
{
	friend class Game;
private:

	MapCell** celdas; //Array dinámico de 2D

public:

	GameMap(Point2D pos, int fils, int cols, Game* g);
	virtual ~GameMap();
	virtual void saveToFile(ofstream& output);
	void render();
	bool intersectWall(const SDL_Rect& rect) const;
};

