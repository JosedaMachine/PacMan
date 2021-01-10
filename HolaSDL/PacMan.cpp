#include "PacMan.h"
#include "PlayState.h"
//Constructora que inicializa pos, vidas, energia y textura.
PacMan::PacMan(Point2D posi, PlayState* pSt, Texture* t, Point2D const size) : GameCharacter(posi, pSt, t, Point2D(10, 0), size)
{
	vidasRow = textureFrame.getY();
	vidasCol = textureFrame.getX();

	energyLeft = 0;

	respawn = 8000000;
}
//Constructora por flujo
PacMan::PacMan(ifstream& input, PlayState* pSt, Texture* t, Point2D const size) : GameCharacter(input, pSt, t, Point2D(10, 0), size)
{
	vidasRow = textureFrame.getY();
	vidasCol = textureFrame.getX();

	energyLeft = 0;
	respawn = 0;
}
//Renderiza la posicion del PacMan y su animacion de "Waka Waka"
void PacMan::render()
{
	GameCharacter::render();
	//Extra | Animacion
	if (textureFrame.getX() == 10) textureFrame.setX(11);
	else textureFrame.setX(10);
}
//Actualiza la posición del pacman y su sprite
 void PacMan::update()
{
	 pS->colissions(getDestRect());
		//actualizamos a la siguiente pos
	 if (pS->tryMove(getDestRect(), nextDir, pos))
	 {
		dir = nextDir;

		if (dir == Vector2D(0, -1)) textureFrame.setY(3);
		else if (dir == Vector2D(0, 1)) textureFrame.setY(1);
		else if (dir == Vector2D(1, 0)) textureFrame.setY(0);
		else  textureFrame.setY(2);
	 }

	 if (pS->tryMove(getDestRect(), dir, pos))
	 {
		pos = pos + dir;

		//Comprobamos si va a aparecer por el otro lado
		pS->ToroidalPos(pos);

		eat();
	 }

	if (energyLeft > 0)--energyLeft;
	else if(energyLeft==0) pS->setGhostsEdables(false);
	
	if (respawn > 0)respawn--;

	pS->colissions(getDestRect());

}
//guarda en un archivo .dat su identificador, posicion inicial, posicion actual y direccion
 void PacMan::saveToFile(ofstream& output)
 {
	 output << 9 << " ";
	 GameCharacter::saveToFile(output);
	 output << endl;
 }
//Muerte (restamos una vida y lo devolvemos a su posicion inicial, además de quitarle la dirección)
void PacMan::death()
{
	if (pS->restLife())
	{
		pos = posIni;
		dir = Vector2D(0, 0);
		nextDir = Vector2D(0, 0);
		respawn = 60 * pS->getGameFrameRate();
	}
}
//Cambia la siguiente dirección del PacMan en función del input
void PacMan::handleEvent(const SDL_Keycode& key)
{
	switch (key)
	{
		case SDLK_UP:
			nextDir = Vector2D(0, -1);
			break;
		case SDLK_DOWN:
			nextDir = Vector2D(0, 1);
			break;
		case SDLK_RIGHT:
			nextDir = Vector2D(1, 0);
			break;
		case SDLK_LEFT:
			nextDir = Vector2D(-1, 0);
			break;
		default:
			break;

	}
}
//Verifica si el jugadro está sobre una celda donde hay comida, y en caso positivo cambia el tipo de esa celda a vacio y aumenta los puntos
//Tambien activa el modo "Comer" a los fantasmas y su energia
void PacMan::eat()
{
	//EL PACMAN ES UN GLOTON Y COME ANTES
	Point2D posCoord;
	
	pS->SDLPointToMapCoords(pos,posCoord);

	int n = pS->getCellType(posCoord);

	if (n == 2 || n == 3) {
		pS->setCell(0, posCoord);
		pS->SumaPuntos(1);
		if(n==2)pS->FoodEaten();
		else {
			energyLeft = 600;
			pS->setGhostsEdables(true);
		}
	}
}
