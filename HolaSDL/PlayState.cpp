#include "PlayState.h"

void Game::load(int lives)
{
	ifstream input;

	if (!wantLoad)
	{
		input.open(Levels[Current_Level]);
		if (!input.is_open()) throw FileNotFoundError("Can't find file " + Levels[Current_Level]);

		input >> fils >> cols;
		if (!input) throw FileFormatError("Format wrong. Data type unexpected.");

		OFFSET_WIDTH = WIN_WIDTH / cols;
		OFFSET_HEIGHT = WIN_HEIGHT / fils;

		map = new GameMap(Point2D(0, 0), fils, cols, this);
		gO.push_back(map);

		bar = new InfoBar(this, Textures[1], Textures[3]);

		for (int i = 0; i < fils; i++) {
			for (int j = 0; j < cols; j++) {
				int n;
				input >> n;
				if (!input) throw FileFormatError("Format wrong. Data type unexpected.");

				if (n < 4) {
					map->celdas[i][j] = (MapCell)n;
					if (n == 2)++amountFood;
				}
				else {
					if (n == 9)
					{
						player = (new PacMan(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT))); //cambio el orden de j e i ya que las columnas( cada una representa una pos en X )
						player->SetItList(gO.insert(gO.end(), player));
						//inserta en el iterador que tu le pasar, el obketo que tu le pasas, y te devuelve el iterador donde se ha insertado
					}
					else if (n != 4) {
						Ghost* newG = new Ghost(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n - 5);
						newG->SetItList(gO.insert(gO.end(), newG));
						Ghosts.push_back(newG);
					}
					else if (n == 4){
						SmartGhost* newG = new SmartGhost(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n, Point2D(12, 1));
						newG->SetItList(gO.insert(gO.end(), newG));
						Ghosts.push_back(newG);
					}
					map->celdas[i][j] = Empty;
				}
			}
		}
	}
	else
	{
		string file = ".//matches//" + user + ".dat";
		input.open(file);

		if (!input.is_open()) 
			throw FileNotFoundError("Can't find file " + user + ".dat");

		loadMatch(input);

		input.close();
	}
	
}
//Cargamos una partida guardada, que contiene el mapa, el número de objetos, vidas y puntuación
void Game::loadMatch(ifstream& input)
{
	input >> lives >> points >> fils >> cols;
	if(!input) throw FileFormatError("Format wrong. Data type unexpected.");

	OFFSET_WIDTH = WIN_WIDTH / cols;
	OFFSET_HEIGHT = WIN_HEIGHT / fils;

	map = new GameMap(Point2D(0, 0), fils, cols, this);
	gO.push_back(map);

	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++) {
			int n;
			input >> n;
			if (!input) throw FileFormatError("Format wrong. Data type unexpected.");

			if (n < 4) {
				map->celdas[i][j] = (MapCell)n;
				if (n == 2)++amountFood;
			}
			else  map->celdas[i][j] = Empty;
		}
	}

	bar = new InfoBar(this, Textures[1], Textures[3]);
	createNPositionate(input);
}
//devolvemos el tipo de casilla en función de una posición dada
int Game::getCellType(Point2D posPlayer) const
{
	return map->celdas[posPlayer.getY()][posPlayer.getX()];
}
//Devuelve la textura relacionada con el Enum y el entero de entrada
Texture* Game::getTexture(TextureName t)
{
	return Textures[(int)t];
}
//resta en una unidad las vidas y devuelve si el jugador sigue vivo
bool Game::restLife()
{
	lives--;
	return lives > 0;
}
//crea los fantasmas y el player dado un flujo de entrada y el numero de objetos
void Game::createNPositionate(ifstream& input)
{
	int gameObjects;
	input >> gameObjects;
	if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
					//no se incluye el mapa
	for (int i = 0; i < gameObjects -1; i++) {
		int n;
		input >> n;
		if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
		if (n == 9) {
			player = new PacMan(input, this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT));
			player->SetItList(gO.insert(gO.end(), player));
		}
		else if (n != 4) {
			Ghost* newG = new Ghost(input, this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n - 4);
			newG->SetItList(gO.insert(gO.end(), newG));
			Ghosts.push_back(newG);
		}
		else {
			SmartGhost* newG = new SmartGhost(input, this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), Point2D(12, 1));
			newG->SetItList(gO.insert(gO.end(), newG));
			Ghosts.push_back(newG);
		}
	}
}
//comprobamos si los fantasmas y el pac-man están en la misma posición y actuamos en consecuencia
void Game::colissions(const SDL_Rect rect) const
{
	for (Ghost* g : Ghosts){		
		SDL_Rect ghostRect = g->getDestRect();
		if (SDL_HasIntersection(&rect, &ghostRect)){
			if (player->GetEnergy() > 0 ) g->death();
			else if (!player->GetRespawn()){
				SmartGhost* fantasmita = dynamic_cast<SmartGhost*>(g);
				if (fantasmita != NULL) if (fantasmita->getState() == Adult || fantasmita->getState() == Quarantine) player->death();
				else player->death();
			}
		}
	}
}
//Comprobamos si un fantasma de tipo SmartGhost ha colisionado con otro fantasma, para asi reproducirse
void Game::collisionGhost(const SDL_Rect rect, Ghost* ghost)
{
	SmartGhost* smart = dynamic_cast<SmartGhost*>(ghost);
	if (smart != NULL){
		for (Ghost* g : Ghosts){
			SDL_Rect ghostRect = g->getDestRect();

			if (!equalRect(rect, ghostRect) && SDL_HasIntersection(&rect, &ghostRect))
				reproduce(smart, g);
		}
	}
}
//Guarda cada uno de los GameObjects del juego, incluyendo las vidas y la puntuación.
void Game::saveToFileGame()
{
	ofstream output;
	string file = ".//matches//" + user + ".dat";
	output.open(file);
	if (!output.is_open()) throw FileNotFoundError("Can't find file" + user + ".dat");

	output << lives << " " << points << endl;
	map->saveToFile(output);

	output << gO.size() << endl;

	for (GameObject* gameOb : gO){
		GameCharacter* gC = dynamic_cast<GameCharacter*>(gameOb);
		if(gC != NULL)
			gC->saveToFile(output);
	}
	output.close();
}
//Metodo que recibe dos fantasmas, los analiza y si corresponde, se crea un nuevo fantasma dependiendo del tipo de los padres
void Game::reproduce(SmartGhost* _father, Ghost* couple)
{
	//Comprobamos solo la madre porque anteriormente comprobamos que lo es el padre
	bool freePos = false;
	int i = 0;

	while(i < 4 && !freePos){
		freePos = tryMove(_father->getDestRect(), _father->getDir(i), _father->GetPos());
		++i;
	}

	//Si no hay hueco, pues no se crea ningún fantasma
	if (i < 4 && _father->getState() == Adult){
		SmartGhost* mother = dynamic_cast<SmartGhost*>(couple);

		if (mother !=NULL){
			if (mother->getState() == Adult){
				SmartGhost* newG = new SmartGhost(_father->GetPos() + _father->getDir(i), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), 4, Point2D(12,1));
				newG->SetItList(gO.insert(gO.end(), newG));
				Ghosts.push_back(newG);
				//Pone a ambos padres en cuarentena
				mother->setState(Quarantine);
				_father->setState(Quarantine);
			}
		}
		else{
			//selecciona un color del padre random.
			int select = (rand() % 3);

			Ghost* newG = new Ghost(_father->GetPos() + _father->getDir(i), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), select);
			newG->SetItList(gO.insert(gO.end(), newG));
			Ghosts.push_back(newG);

			_father->setState(Quarantine);
		}
	}
}
//Dada una poscición y un n que hace referencia al tipo de celda, cambiamos el valor en el mapa
void Game::setCell(int n, Point2D posPlayer)
{
	map->celdas[posPlayer.getY()][posPlayer.getX()] = (MapCell)n;
}
