#pragma once
#include "texture.h"
#include "checkML.h"
class Game;

class InfoBar
{
private:
	Texture* lifes;
	Texture* numbers;

	int maxLifes, maxDigits;
	int lifesCol, lifesRow;
	int points, vidas;

	Game * g;
public:

	InfoBar(Game* game, Texture* lives, Texture* digits);

	void render()const;
	void updateInfo(int vidas, int points);

private:
	void renderNum(const SDL_Rect& destRect, int n) const;
};

