 #pragma once
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"
#include "GameCharacter.h"

class PlayState;

class PacMan : public GameCharacter
{

private:
	
	int energyLeft;
	int vidasRow, vidasCol;
	int respawn; //Para que no te maten nada más aparecer

public:

	PacMan(Point2D posi, PlayState* game, Texture* t, Point2D const size);
	PacMan(ifstream& input, PlayState* game, Texture* t, Point2D const size);

	void render();

	virtual void update();
	virtual void saveToFile(ofstream& output);

	void death();
	void handleEvent(const SDL_Keycode&event);
	void eat();

#pragma region GETTERS
	Point2D GetPos() const { return pos; }
	int GetEnergy()const { return energyLeft; }
	bool GetRespawn() const { return respawn > 0; }
#pragma endregion

};

