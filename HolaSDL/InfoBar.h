#pragma once
#include "texture.h"
#include "checkML.h"
class PlayState;
//InfoBar tiene que ser un GameObject?
class InfoBar
{
private:
	Texture* lifes;
	Texture* numbers;

	int maxLifes, maxDigits;
	int lifesCol, lifesRow;
	int points, vidas;

	PlayState * pS;

public:

	InfoBar(PlayState* game, Texture* lives, Texture* digits);

	void render()const;
	void updateInfo(int vidas, int points);

private:
	void renderNum(const SDL_Rect& destRect, int n) const;
};

