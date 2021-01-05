#include "Vector2D.h"
#include "SDL.h"
#include <fstream>


#pragma once
class Game;

class GameObject
{
protected:
	//Tamaño del game object en pantalla
	int height, width;
	Game* g;
	Point2D pos;
public:

	GameObject();
	GameObject(Point2D pos, int w, int h, Game* g): pos(pos), width(w), height(h), g(g){};

	//Abstracto
	virtual ~GameObject() {};

	virtual void render() = 0; //si no le pongo const, no funka
	virtual void update() {}; // si pongo = 0 tengo que redefinirlo obligatoriamente, de lo contrario seria opcional

	//Virtual
	virtual SDL_Rect getDestRect() { 
		SDL_Rect destRect;
		destRect.w = width;
		destRect.h = height;
		
		destRect.x = pos.getX();
		destRect.y = pos.getY();
		
		return destRect;
	}
};


