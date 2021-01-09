#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* game, TextureManager* tM) : GameState(game, tM)
{
	load(3);
	wantLoad = false;
}

PlayState::~PlayState()
{
	delete bar;

	for (GameObject* gameOb : gO) delete gameOb;
	Ghosts.clear();
	gO.clear();
}

void PlayState::load(int lives)
{
	ifstream input;

	if (!wantLoad)
	{
		input.open(Levels[Current_Level]);
		if (!input.is_open()) throw FileNotFoundError("Can't find file " + Levels[Current_Level]);

		input >> fils >> cols;
		if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
		OFFSET_WIDTH = g->getWidth()/ cols;
		OFFSET_HEIGHT = g->getHeight()/ fils;

		map = new GameMap(Point2D(0, 0), fils, cols, this);
		gO.push_back(map);

		bar = new InfoBar(this, tM->getTexture(Characters), tM->getTexture(Digits));

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
						player = (new PacMan(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT))); //cambio el orden de j e i ya que las columnas( cada una representa una pos en X )
						player->SetItList(gO.insert(gO.end(), player));
						//inserta en el iterador que tu le pasar, el obketo que tu le pasas, y te devuelve el iterador donde se ha insertado
					}
					else if (n != 4) {
						Ghost* newG = new Ghost(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n - 5);
						newG->SetItList(gO.insert(gO.end(), newG));
						Ghosts.push_back(newG);
					}
					else if (n == 4){
						SmartGhost* newG = new SmartGhost(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n, Point2D(12, 1));
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
		string file = ".//matches.dat//" /*+ user + ".dat"*/;
		input.open(file);

		if (!input.is_open()) 
			throw FileNotFoundError("Can't find file .dat" /*+ user + ".dat"*/);

		loadMatch(input);

		input.close();
	}
	
}
//Cargamos una partida guardada, que contiene el mapa, el número de objetos, vidas y puntuación
void PlayState::loadMatch(ifstream& input)
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

	bar = new InfoBar(this, tM->getTexture(Characters), tM->getTexture(Digits));
	createNPositionate(input);
}
int PlayState::getWindowWidth() const
{
	return g->getWidth();
}
int PlayState::getWindowHeight() const
{
	return g->getHeight();
}
int PlayState::getGameFrameRate() const
{
	return g->getFrameRate();
}
//devolvemos el tipo de casilla en función de una posición dada
int PlayState::getCellType(Point2D posPlayer) const
{
	return map->celdas[posPlayer.getY()][posPlayer.getX()];
}

void PlayState::Borra()
{
	for (auto gameOb : objectsToErase)
	{
		delete *gameOb; //es un iterador y hay que eliminar el objeto de la lista
		//erase elimina el Nodo donde esta ubicado el iterador
		gO.erase(gameOb);
	}
	objectsToErase.clear(); //borrar iteradores de la lista
}
void PlayState::update()
{
	if (GetRunning()) {
		GameState::update();

		if (amountFood == 0)
		{
			if (Current_Level < Levels.size()) changeLevel();
			else  hasWon = true;
		}

		Borra();
	}
	else {

	}
}
void PlayState::render()
{
	GameState::render();

	//estos valores hay que cambiarlos para que sean una referencia y no hacer el Update en el render
	bar->updateInfo(lives, points);
	bar->render();
}
//resta en una unidad las vidas y devuelve si el jugador sigue vivo
bool PlayState::restLife()
{
	lives--;
	return lives > 0;
}
//Cambia el nivel en caso de que haya terminado de consumir todas las celdas de comida. Reinicia la puntuación pero mantiene las vidas.
void PlayState::changeLevel()
{
	int currentLifes = lives;
	
	for (GameObject* gameOb : gO) delete gameOb;
	
	Ghosts.clear();
	gO.clear();
	
	Current_Level++;
	points = 0;
	
	load(currentLifes);
}
//Suma puntos
void PlayState::SumaPuntos(int cantidad)
{
	points += cantidad;
}
//Comprueba si uno de los personajes ha salido de pantalla y le permite transportarse al otro lado
void PlayState::ToroidalPos(Point2D& pos)
{
	SDL_Rect mapRect = map->getDestRect();

	if (pos.getX() + OFFSET_WIDTH > mapRect.x + map->width*OFFSET_WIDTH) pos = Point2D(mapRect.x, pos.getY());
	else if (pos.getX() < mapRect.x) 
		pos = Point2D(mapRect.x + map->width * OFFSET_WIDTH - OFFSET_WIDTH, pos.getY());
	else if (pos.getY() > mapRect.y + map->width*OFFSET_HEIGHT) 
		pos = Point2D(pos.getX(), mapRect.y+OFFSET_HEIGHT);
	else if (pos.getY() < mapRect.y + OFFSET_HEIGHT) pos = Point2D(pos.getX(), mapRect.y + map->width * OFFSET_HEIGHT);
}
////Coloca a cada fantasma como "comible" o no
void PlayState::setGhostsEdables(bool eda)
{
	 for (Ghost* g : Ghosts) g->setEdable(eda);
}
//crea los fantasmas y el player dado un flujo de entrada y el numero de objetos
void PlayState::createNPositionate(ifstream& input)
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
			player = new PacMan(input, this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT));
			player->SetItList(gO.insert(gO.end(), player));
		}
		else if (n != 4) {
			Ghost* newG = new Ghost(input, this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n - 4);
			newG->SetItList(gO.insert(gO.end(), newG));
			Ghosts.push_back(newG);
		}
		else {
			SmartGhost* newG = new SmartGhost(input, this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), Point2D(12, 1));
			newG->SetItList(gO.insert(gO.end(), newG));
			Ghosts.push_back(newG);
		}
	}
}
//comprobamos si los fantasmas y el pac-man están en la misma posición y actuamos en consecuencia
void PlayState::colissions(const SDL_Rect rect) const
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
void PlayState::handleEvent(SDL_Event& event)
{
	SDL_Keycode key = event.key.keysym.sym;

	//   ;(
	player->handleEvent(key);
	//el handle event del player, sacar el menu y esas cosas
}
//Convierte las coordenadas de las celdas a pixeles
void PlayState::mapCoordToSDLPoint(Point2D old, Point2D& newP)
 {
	 newP.setX(old.getX()* OFFSET_WIDTH);
	 newP.setY(old.getY() * OFFSET_HEIGHT + OFFSET_HEIGHT);
 }
//Convierte las coordenadas de pixeles a celdas del mapa
void PlayState::SDLPointToMapCoords(Point2D old, Point2D& newP)
 {
	 newP.setX(old.getX() / OFFSET_WIDTH);
	 newP.setY((old.getY() - OFFSET_HEIGHT ) / OFFSET_HEIGHT);
 }
//Comprobamos si un fantasma de tipo SmartGhost ha colisionado con otro fantasma, para asi reproducirse
void PlayState::collisionGhost(const SDL_Rect rect, Ghost* ghost)
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
//Comprueba si el siguiente pixel es válido para moverse
bool PlayState::tryMove(SDL_Rect rect, Vector2D dir, Point2D Pos)
 {
	 SDL_Rect newRect;
	 Point2D newPos = Pos + dir;
	 newRect.w = rect.w;
     newRect.h = rect.h;
		
	 newRect.x = newPos.getX();
	 newRect.y = newPos.getY();

	 //Si no ha intersectado (false) se nega para que pueda avanzar.
	 return !map->intersectWall(newRect);
 }
//almacena los fantasmas que han muerto para luego eliminarlos de la escena
void PlayState::borraFantasma(list<GameObject*>::iterator it, Ghost* fantasma)
 {
	 Ghosts.remove(fantasma);
	 objectsToErase.push_back(it);
 }
//Guarda cada uno de los GameObjects del juego, incluyendo las vidas y la puntuación.
void PlayState::saveToFileGame()
{
	ofstream output;
	string file = ".//matches//" /*+ user + ".dat"*/;
	output.open(file);
	if (!output.is_open()) throw FileNotFoundError("Can't find file" /*+ user + ".dat"*/);

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
void PlayState::reproduce(SmartGhost* _father, Ghost* couple)
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
				SmartGhost* newG = new SmartGhost(_father->GetPos() + _father->getDir(i), this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), 4, Point2D(12,1));
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

			Ghost* newG = new Ghost(_father->GetPos() + _father->getDir(i), this, tM->getTexture(Characters), Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), select);
			newG->SetItList(gO.insert(gO.end(), newG));
			Ghosts.push_back(newG);

			_father->setState(Quarantine);
		}
	}
}
//Dada una poscición y un n que hace referencia al tipo de celda, cambiamos el valor en el mapa
void PlayState::setCell(int n, Point2D posPlayer)
{
	map->celdas[posPlayer.getY()][posPlayer.getX()] = (MapCell)n;
}
