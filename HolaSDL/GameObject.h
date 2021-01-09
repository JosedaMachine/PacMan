#include "Vector2D.h"
#include "SDL.h"
#include <fstream>


#pragma once
class GameState;

class GameObject
{
protected:
	//Tamaño del game object en pantalla
	int height, width;
	GameState* gS;
	Point2D pos;
public:

	GameObject();
	GameObject(Point2D pos, int w, int h, GameState* gSt): pos(pos), width(w), height(h), gS(gSt){};

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


