#include "SmartGhost.h"
#include "PlayState.h"
//Constructora del Fantasma en cuestión, que recibe una textura, su posicion. Inicializa los atributos adecuados, como el estado y la edad.
SmartGhost::SmartGhost(Point2D initPos, PlayState* game, Texture* t, Point2D size, int colText, Point2D deadT) : Ghost(initPos, game, t, size, colText)
{
	state = Child;
	age = 0;
	deadText = deadT;
}
//Constructora por copia
SmartGhost::SmartGhost(ifstream& input, PlayState* game, Texture* t, Point2D const size, Point2D const deadT) : Ghost(input, game, t, size, 4)
{
	state = Child;
	deadText = deadT;

	input >> age;
}
//Renderiza al fantasma en su posición y con su sprite adecuado.
void SmartGhost::render()
{
	SDL_Rect destRect = getDestRect();

	if (state == Child) {
		destRect.w = destRect.w * 3 / 4;
		destRect.h = destRect.h * 3 / 4;
		destRect.x = destRect.x + (width / 4);
		destRect.y = destRect.y + (height / 4);
	}

	if (state != Dead)texture->renderFrame(destRect, textureFrame.getY(), textureFrame.getX());
	else texture->renderFrame(destRect, deadText.getY(), deadText.getX());
;
}
//Actualiza la posición y el sprite del fantasma
void SmartGhost::update()
{
	SmartGhost* gh = this;
	gS->collisionGhost(getDestRect(), gh);

	if (state != Dead) {
		Point2D newDir = gS->PlayerPos() - pos;
		if (newDir.module() > 150) Ghost::update();
		else
		{
			checkSmartDir(newDir);
			//actualizamos a la siguiente pos
			pos = pos + dir;
			//Comprobamos si va a aparecer por el otro lado
			gS->ToroidalPos(pos);
			//Cambiamos el Sprite en caso de que sea comible
			if (!edable)
				ChangeSprite();
		}

		if (state == Child && age >= tiempoDeNiño && age < tiempoDeVida) state = Adult;
		else if(age > tiempoDeVida) state = Dead;

		if (timerCuarentena > 0) { 
			timerCuarentena--;
		}
	}
	else if (age > tiempoDeDescomposicion) {
		gS->borraFantasma(it, this);
	}
	age++;

	gS->collisionGhost(getDestRect(), this);
}
//guarda en un archivo .dat su identificador, posicion inicial, posicion actual y direccion
void SmartGhost::saveToFile(ofstream& output)
{
	output << 4 << " ";
	GameCharacter::saveToFile(output);

	output << age << endl;
}
//Comprueba la siguiente posición y cambia la siguiente dirección y si el jugador está en su alcance, se dirige a él o huye de él
void SmartGhost::checkSmartDir(Point2D newDir)
{
	//array de candidatos
	Vector2D candidates[2];
	Vector2D opst = dir.oposite();
	int numCandidates = 0;

	
	//Si es comible, el fantasma huye
	if (edable)
		newDir = newDir.oposite();

	//Normalizamos el vector resultado.
	newDir.normalize();

	//para que vallan por casillas
	SDL_Rect GhostRect = getDestRect();

	Point2D newPos, posCor;
	newPos.setX(GhostRect.x);
	newPos.setY(GhostRect.y);
	newPos = newPos + dir;
	gS->SDLPointToMapCoords(newPos, newPos);
	gS->SDLPointToMapCoords(pos, posCor);

	//Dos candidatos máximo
	//Elige exactamente dos candidatos respecto a la pos actual del Player
	if (newPos != posCor || !gS->tryMove(GhostRect, dir, pos) || dir == Point2D(0, 0))
	{
		//Comprobacion de que puede ir por arriba o por abajo
		if (gS->tryMove(getDestRect(), Point2D(newDir.getX(), 0), pos))
		{
			candidates[0] = Point2D(newDir.getX(), 0);
			numCandidates++;
		}
		else {
			candidates[0] = Point2D(-newDir.getX(), 0);
			numCandidates++;
		}

		//Comprobacion de que puede ir por la derecha o la izquierda
		if (gS->tryMove(getDestRect(), Point2D(0, newDir.getY()), pos))
		{
			candidates[1] = Point2D(0, newDir.getY());
			numCandidates++;
		}
		else {
			candidates[1] = Point2D(0, -newDir.getY());
			numCandidates++;
		}

		//selecciona uno de los posibles candidatos y si esta en un callejón, se da la vuelta
		if (numCandidates != 0)
		{
			int select = (rand() % numCandidates);
			dir = candidates[select];
		}
		else dir = opst;
	}	
}
//Establece el estado del fantasma 
void SmartGhost::setState(State st)
{
	state = st;
	if (st == Quarantine) timerCuarentena = tiempoEnCuanrentena;
}
