#pragma once
#include "GameObject.h"
#include "texture.h"
#include "checkML.h"
class PlayState;
//InfoBar GameObject para no tener que llamar a sus métodos por separado
class InfoBar : public GameObject
{
private:
	Texture* lifes;
	Texture* numbers;

	int maxLifes, maxDigits;
	int lifesCol, lifesRow;
	int* points,* vidas;

	PlayState * pS;

public:

	InfoBar(PlayState* game, Texture* lives, Texture* digits, int& vidas, int& puntos);

	virtual void render();

private:
	void renderNum(const SDL_Rect& destRect, int n) const;
};

