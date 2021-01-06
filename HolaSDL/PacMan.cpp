#include "PacMan.h"
#include "Game.h"
//Constructora que inicializa pos, vidas, energia y textura.
PacMan::PacMan(Point2D posi, Game* game, Texture* t, Point2D const size) : GameCharacter(posi, game, t, Point2D(10, 0), size)
{
	vidasRow = textureFrame.getY();
	vidasCol = textureFrame.getX();

	energyLeft = 0;

	respawn = 0;
}
//Constructora por flujo
PacMan::PacMan(ifstream& input, Game* game, Texture* t, Point2D const size) : GameCharacter(input, game, t, Point2D(10, 0), size)
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
	 g->colissions(getDestRect());
		//actualizamos a la siguiente pos
	 if (g->tryMove(getDestRect(), nextDir, pos))
	 {
		dir = nextDir;

		if (dir == Vector2D(0, -1)) textureFrame.setY(3);
		else if (dir == Vector2D(0, 1)) textureFrame.setY(1);
		else if (dir == Vector2D(1, 0)) textureFrame.setY(0);
		else  textureFrame.setY(2);
	 }

	 if (g->tryMove(getDestRect(), dir, pos))
	 {
		pos = pos + dir;

		//Comprobamos si va a aparecer por el otro lado
		g->ToroidalPos(pos);

		eat();
	 }

	if (energyLeft > 0)--energyLeft;
	else if(energyLeft==0) g->setGhostsEdables(false);
	
	if (respawn > 0)respawn--;

	g->colissions(getDestRect());

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
	if (g->restLife())
	{
		pos = posIni;
		dir = Vector2D(0, 0);
		nextDir = Vector2D(0, 0);
		respawn = 60 * g->getFrameRate();
	}
}
//Cambia la siguiente dirección del PacMan en función del input
void PacMan::handleEvent(const SDL_Keycode& key)
{
	//SDL_Keycode key = event.key.keysym.sym;

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
	
	g->SDLPointToMapCoords(pos,posCoord);

	int n = g->getCellType(posCoord);

	if (n == 2 || n == 3) {
		g->setCell(0, posCoord);
		g->SumaPuntos(1);
		if(n==2)g->FoodEaten();
		else {
			energyLeft = 600;
			g->setGhostsEdables(true);
		}
	}
}
