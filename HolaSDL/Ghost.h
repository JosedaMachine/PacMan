#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "GameCharacter.h"

#include "checkML.h"
#include <array>
#include <cstdlib> 


const int NUM_DIR = 4;

class Game;
class Ghost : public GameCharacter
{
protected:
	//Controlador de si es comible
	bool edable;
	//ARRAY DE DIRECCIONES
	const array<Vector2D, NUM_DIR> directions = { Vector2D(-1,0), Vector2D(0,1), Vector2D(0,-1), Vector2D(1, 0) };
	//Direcciones
	//Vector2D dir, nextDir;
	int rowTextureEdable, colTextureEdable;
	//Para guardar las texturas originales
	Point2D auxTextures;

public:
	Ghost(Point2D initPos, Game* game, Texture* t, Point2D const size, int colText );
	Ghost(ifstream& input, Game* game, Texture* t, Point2D const size, int colText);

	void render();
	virtual void update();
	virtual void saveToFile(ofstream& output);

	void death();
	void ChangeSprite();
	void checkNextDir();
	void setEdable(bool eda);

	Point2D getDir(int i) { return directions[i]; }
	Point2D GetPos() const { return pos; }
};

