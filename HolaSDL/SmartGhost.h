#pragma once
#include "Ghost.h"
class Game;
enum State {Child, Adult, Quarantine, Dead};
class SmartGhost : public Ghost
{
	State state;
	int age;
	Point2D deadText;
	int timerCuarentena = 0;
	
	int tiempoEnCuanrentena = 2500;
	int tiempoDeNiño = 500;
	int tiempoDeVida = 3400;
	int tiempoDeDescomposicion = 4000;

public:

	SmartGhost(Point2D initPos, Game* game, Texture* t, Point2D const size, int colText, Point2D const deadT);
	SmartGhost(ifstream& input, Game* game, Texture* t, Point2D const size, Point2D const deadT);
	void render(); 
	virtual void update();
	virtual void saveToFile(ofstream& output);
	void checkSmartDir(Point2D pacmanPos);

	State getState() { return state; }
	void setState(State st);
	
};

