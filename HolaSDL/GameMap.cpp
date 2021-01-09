#include "GameMap.h"
#include "Game.h"
#include "PlayState.h"

//Constructora
GameMap::GameMap(Point2D pos, int f, int c, PlayState* game) : GameObject(pos, c, f, game)
{
	celdas = new MapCell *[height];

	for (int i = 0; i < height; i++)
		celdas[i] = new MapCell[width];
}
//Destructora(borramos memoria dinámica)
GameMap::~GameMap()
{
	for (size_t i = 0; i < height; i++)
		delete[] celdas[i];

	delete[] celdas;
}
//Guardamos los datos del mapa
void GameMap::saveToFile(ofstream& output)
{
	output << height <<" "<<width << endl;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++)
			output << (int)celdas[i][j] << " ";

		output << endl;
	}
}
//Renderiza el mapa con las texturas correspondientes: Vitaminas, Comida, y Muro.
void GameMap::render() 
{
	Texture* wall = gS->tM->getTexture(WallMap);
	Texture* food = gS->tM->getTexture(Food);
	Texture* vitamins = gS->tM->getTexture(PowerUp);

	SDL_Rect destRect;
	
	destRect.w = gS->getOffsetWidth();
	destRect.h = gS->getOffsetHeight();
	destRect.y = gS->getOffsetHeight();

	for (int i = 0; i < height; i++)
	{
		destRect.x = 0;

		for (int j = 0; j < width; j++)
		{
			if (celdas[i][j] == Wall)wall->render(destRect);
			else if (celdas[i][j] == Foodie)food->render(destRect);
			else if (celdas[i][j] == Vitamins)vitamins->render(destRect);

			destRect.x += destRect.w;
		}
		destRect.y += destRect.h;
	}
}
//Detecta si un rectángulo tiene intersección con un muro
bool GameMap::intersectWall(const SDL_Rect& rect) const
{
	Point2D iz(rect.x, rect.y);
	Point2D der(rect.x + rect.w -1 , rect.y + rect.h - 1);
	Point2D topLeft, botRight;

	//Metodo que tiene el estado PlayState
	gS->SDLPointToMapCoords(iz, topLeft);
	gS->SDLPointToMapCoords(der, botRight);
	//Comprobamos si alguna de las esquinas intersecta con un muro, ya que el PacMan puede estar en dos casillas al mismpo tiempo.
	//En definitiva estamos comprobando las cuatro esquinas
	for (int cols = topLeft.getX(); cols <= botRight.getX(); cols++)
		for (int rows = topLeft.getY(); rows <= botRight.getY(); rows++)
			if (celdas[rows][cols] == Wall) return true;

	return false;
}


