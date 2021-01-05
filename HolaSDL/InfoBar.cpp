#include "InfoBar.h"
#include "Game.h"
//Constructora de la barra HUB
InfoBar::InfoBar(Game* game, Texture* life, Texture* digits)
{
	maxLifes = 3;
	maxDigits = 3;

	g = game;
	
	lifes = life;
	numbers = digits;

	lifesRow = 0;
	lifesCol = 10;

	points = 0;
	vidas = 3;
}
//Pinta las vidas y los puntos
void InfoBar::render() const
{
	SDL_Rect destRect;

	destRect.w = g->getOffsetWidth();
	destRect.h = g->getOffsetHeight();

	//VIDAS
	destRect.x = 0; destRect.y = 0;

	for (int i = 0; i < vidas; i++)
	{
		lifes->renderFrame(destRect, lifesRow, lifesCol);
		destRect.x += destRect.w;	
	}

	//PUNTOS
	destRect.x = g->getWidth() - g->getOffsetWidth();

	int n = points;

	for(int i = 0; i<maxDigits;i++)
	{
		int digit = n % 10;
		renderNum(destRect, digit);
		n = n / 10;
		destRect.x = destRect.x - g->getOffsetWidth();
	}
}
//Actualiza la informacion de la barra HUD. Tanto las vidas como los puntos
void InfoBar::updateInfo(int vids, int point)
{
	vidas = vids;
	points = point;
}
//Dibuja los números de la puntuación
void InfoBar::renderNum(const SDL_Rect& destRect, int n) const
{
	const int op = 4;

	int i = n / op; //ROW
	int j = n - i * op; //COL

	numbers->renderFrame(destRect, i, j);
}