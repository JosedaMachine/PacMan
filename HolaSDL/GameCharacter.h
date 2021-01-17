#include "GameObject.h"
#include "Vector2D.h";
#include <list>
#pragma once

class PlayState;

class GameCharacter : public GameObject
{
public:
	PlayState* pS;
	virtual void saveToFile(ofstream& output);
	virtual void SetItList(list<GameObject*>::iterator p) { it = p; };
	virtual void render();
protected: 
	Point2D posIni, posToRender;
	Vector2D dir, nextDir;
	Texture* texture;
	Point2D textureFrame;
	list<GameObject*>::iterator it;

	GameCharacter(Point2D posInitial, PlayState* pSt, Texture* t, Point2D textureFrame, Point2D const size);
	GameCharacter(ifstream& input, PlayState* pSt , Texture* t, Point2D textureFrame , Point2D size);

	//No se declaera un update porque cada hijo lo redefine y no hay que hacer nada en especial en GameCharacte

	//por convenio
};
