#include "InfoBar.h"
#include "PlayState.h"
//Constructora de la barra HUB
//ESTO HAY QUE ARREGLARLO PARA QUE HEREDE BIEN
InfoBar::InfoBar(PlayState* pSt, Texture* life, Texture* digits, int* lives, int* point) : GameObject(Point2D(0,0), 0, 0)
{
	maxLifes = 3;
	maxDigits = 3;

	pS = pSt;
	
	lifes = life;
	numbers = digits;

	lifesRow = 0;
	lifesCol = 10;

	points = point;
	vidas = lives;
}
//Pinta las vidas y los puntos
void InfoBar::render() 
{
	SDL_Rect destRect;

	destRect.w = pS->getOffsetWidth();
	destRect.h = pS->getOffsetHeight();

	//VIDAS
	destRect.x = 0; destRect.y = 0;

	for (int i = 0; i < *vidas; i++)
	{
		lifes->renderFrame(destRect, lifesRow, lifesCol);
		destRect.x += destRect.w;	
	}

	//PUNTOS
	destRect.x = pS->getWindowWidth() - pS->getOffsetWidth();

	int n = *points;

	for(int i = 0; i<maxDigits;i++)
	{
		int digit = n % 10;
		renderNum(destRect, digit);
		n = n / 10;
		destRect.x = destRect.x - pS->getOffsetWidth();
	}
}
//Actualiza la informacion de la barra HUD. Tanto las vidas como los puntos
//Dibuja los números de la puntuación
void InfoBar::renderNum(const SDL_Rect& destRect, int n) const
{
	const int op = 4;

	int i = n / op; //ROW
	int j = n - i * op; //COL

	numbers->renderFrame(destRect, i, j);
}