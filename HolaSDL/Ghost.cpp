#include "Ghost.h"
#include "PlayState.h"
#include <ctime>
//Constructora del Fantasma en cuestión, que recibe una textura, su posicion. 
Ghost::Ghost(Point2D initPosi, PlayState* game, Texture* t, Point2D const size, int colText) : GameCharacter(initPosi, game, t, Point2D(colText * 2, 0), size)
{
	auxTextures = Point2D(textureFrame.getX(), textureFrame.getY());
	edable = false;

	rowTextureEdable = 0;
	colTextureEdable = 12;
	srand(time(nullptr));
}
//Constructora por copia
Ghost::Ghost(ifstream& input, PlayState* game, Texture* t, Point2D const size, int colText) : GameCharacter(input, game, t, Point2D(colText * 2, 0), size)
{
	auxTextures = Point2D(textureFrame.getX(), textureFrame.getY());
	edable = false;

	rowTextureEdable = 0;
	colTextureEdable = 12;
	srand(time(nullptr));
}
//Renderiza al fantasma en su posición y con su sprite adecuado.
void Ghost::render()
{
	GameCharacter::render();

	if (textureFrame.getX() % 2 == 0) textureFrame.setX(textureFrame.getX() + 1);
	else textureFrame.setX(textureFrame.getX()-1);
}
//Actualiza la posición y el sprite del fantasma
void Ghost::update()
{
	checkNextDir();
	//actualizamos a la siguiente pos
	
	pos = pos + dir;
	//Comprobamos si va a aparecer por el otro lado
	pS->ToroidalPos(pos);
	//Cambiamos el Sprite en caso de que sea comible

	if(!edable)
		ChangeSprite();
}
//guarda en un archivo .dat su identificador, posicion inicial, posicion actual y direccion
void Ghost::saveToFile(ofstream& output)
{
	if(textureFrame.getX() == 1)
		output << 5 << " ";
	else output << textureFrame.getX() / 2 + 4 << " ";
	GameCharacter::saveToFile(output); 

	output << endl;
}
//Lleva al fantasma a su posición inicial
void Ghost::death()
{
	pos = posIni;
}
//Cambia el sprite del fantasma en función de la dirección que lleva
void Ghost::ChangeSprite() 
{
	if (dir == Vector2D(0, -1)) textureFrame.setY(3);
	else if (dir == Vector2D(0, 1)) textureFrame.setY(1);
	else if (dir == Vector2D(1, 0)) textureFrame.setY(0);
	else  textureFrame.setY(2);
}
//Comprueba la siguiente posición y cambia la siguiente dirección
void Ghost::checkNextDir()
{
	//array de candidatos
	Vector2D candidates[NUM_DIR];
	Vector2D opst = dir.oposite();
	int numCandidates = 0;
	SDL_Rect GhostRect = getDestRect();

	Point2D newPos, posCor;
	newPos.setX(GhostRect.x);
	newPos.setY(GhostRect.y);
	newPos=newPos + dir;
	pS->SDLPointToMapCoords(newPos, newPos);
	pS->SDLPointToMapCoords(pos, posCor);
		
	if(newPos!=posCor || !pS->tryMove(GhostRect, dir, pos) || dir == Point2D(0,0)){
			//Recorrido para buscar una dirección válida
		for (int i = 0; i < directions.size(); i++){
			if (directions[i] != opst)
				if (pS->tryMove(GhostRect, directions[i], pos)){
					candidates[numCandidates] = directions[i];
					numCandidates++;
				}
		}
		//En caso de que llegue a un callejon sin salida, que tome la direccion opuesta a la actual
		if (numCandidates != 0){
			int select = (rand()%numCandidates);
			dir = candidates[select];

			if (pS->tryMove(GhostRect, dir, pos) == false)
				int n = 0;
		}
		else dir = opst;
	}
}
//Hace que pacman pueda comerse o no comerse a los fantasmas en función del valor que se le introduzca
void Ghost::setEdable(bool eda)
{
	edable = eda;
	if(edable){
		textureFrame.setX(colTextureEdable);
		textureFrame.setY(rowTextureEdable);
	}
	else{
		textureFrame.setX(auxTextures.getX());
		textureFrame.setY(auxTextures.getY());
	}
}

