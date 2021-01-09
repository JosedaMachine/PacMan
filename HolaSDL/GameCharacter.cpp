#include "PlayState.h"
#include "GameCharacter.h"

//Constructora que incializa los atributos del GameCharacter y el GameObject																													//esta es la current 
GameCharacter::GameCharacter(Point2D posInitial, PlayState* pSt, Texture* t, Point2D textureF, Point2D const size) : GameObject(posInitial, size.getX(), size.getY())
{
	texture = t;
	dir = Point2D(0, 0);
	nextDir = dir;
	textureFrame = textureF;
	//Puntero al estado del Juego
	pS = pSt;
	//para respaunear
	posIni = posInitial;
}
//Constructora por flujo
GameCharacter::GameCharacter(ifstream& input, PlayState* pSt, Texture* t, Point2D textureF, Point2D size)
{
	texture = t;
	textureFrame = textureF;
	dir = Point2D(0, 0);
	height = size.getY();
	width = size.getX();
	pS = pSt;

	//Variables de lectura
	int x, y;
	//Posicion Inicial
	input >> x >> y;
	Point2D posi (x, y); 
	
	pS->mapCoordToSDLPoint(posi,posIni);

	input >> x >> y;
	posi.setX(x);
	posi.setY(y);

	pS->mapCoordToSDLPoint(posi, pos);
	//Posicion actual
	input >> x >> y;
	nextDir = Vector2D(x, y);
}
//Guardado de los datos importates como la pos inicial, actual y la dirección
void GameCharacter::saveToFile(ofstream& output)
{
	Point2D actPos;
	pS->SDLPointToMapCoords(posIni, actPos);
	output << actPos.getX() << " " << actPos.getY() << " ";

	pS->SDLPointToMapCoords(pos, actPos);

	output << actPos.getX() << " " << actPos.getY() << " ";
	output << dir.getX() << " " << dir.getY() << " ";
}
//Renderizado genérico de los personajes del juego
void GameCharacter::render()
{
	SDL_Rect destRect = getDestRect();
	
	texture->renderFrame(destRect,textureFrame.getY(), textureFrame.getX());
}
