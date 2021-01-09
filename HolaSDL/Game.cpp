#include "Game.h"
#include <ctime>
Game::Game()
{
	menu();

	#pragma region SDL_INIT
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("PAC-MAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//Codigo Defensivo
	if (window == nullptr || renderer == nullptr) throw SDLError("Error loading window o renderer.");
	#pragma endregion
	tM = new TextureManager(renderer);
	stateMachine = new GameStateMachine();
	stateMachine->pushState(new MainMenuState(this, tM));

	exit = false;
	hasSaved = false;

	
	srand(time(nullptr));
}
//Borramos toda la memoria dinámica que se había creado
Game::~Game()
{
	delete stateMachine;
	delete tM;

	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
//Cargamos toda la información necesaria para el juego, el mapa, las posiciones de fantasmas y jugador y el número de filas y columnas
//void Game::load(int lives)
//{
//	ifstream input;
//
//	if (!wantLoad)
//	{
//		input.open(Levels[Current_Level]);
//		if (!input.is_open()) throw FileNotFoundError("Can't find file " + Levels[Current_Level]);
//
//		input >> fils >> cols;
//		if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
//
//		OFFSET_WIDTH = WIN_WIDTH / cols;
//		OFFSET_HEIGHT = WIN_HEIGHT / fils;
//
//		map = new GameMap(Point2D(0, 0), fils, cols, this);
//		gO.push_back(map);
//
//		bar = new InfoBar(this, Textures[1], Textures[3]);
//
//		for (int i = 0; i < fils; i++) {
//			for (int j = 0; j < cols; j++) {
//				int n;
//				input >> n;
//				if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
//
//				if (n < 4) {
//					map->celdas[i][j] = (MapCell)n;
//					if (n == 2)++amountFood;
//				}
//				else {
//					if (n == 9)
//					{
//						player = (new PacMan(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT))); //cambio el orden de j e i ya que las columnas( cada una representa una pos en X )
//						player->SetItList(gO.insert(gO.end(), player));
//						//inserta en el iterador que tu le pasar, el obketo que tu le pasas, y te devuelve el iterador donde se ha insertado
//					}
//					else if (n != 4) {
//						Ghost* newG = new Ghost(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n - 5);
//						newG->SetItList(gO.insert(gO.end(), newG));
//						Ghosts.push_back(newG);
//					}
//					else if (n == 4){
//						SmartGhost* newG = new SmartGhost(Point2D(j * OFFSET_WIDTH, i * OFFSET_HEIGHT + OFFSET_HEIGHT), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n, Point2D(12, 1));
//						newG->SetItList(gO.insert(gO.end(), newG));
//						Ghosts.push_back(newG);
//					}
//					map->celdas[i][j] = Empty;
//				}
//			}
//		}
//	}
//	else
//	{
//		string file = ".//matches//" + user + ".dat";
//		input.open(file);
//
//		if (!input.is_open()) 
//			throw FileNotFoundError("Can't find file " + user + ".dat");
//
//		loadMatch(input);
//
//		input.close();
//	}
//	
//}
//Cargamos una partida guardada, que contiene el mapa, el número de objetos, vidas y puntuación
//void Game::loadMatch(ifstream& input)
//{
//	input >> lives >> points >> fils >> cols;
//	if(!input) throw FileFormatError("Format wrong. Data type unexpected.");
//
//	OFFSET_WIDTH = WIN_WIDTH / cols;
//	OFFSET_HEIGHT = WIN_HEIGHT / fils;
//
//	map = new GameMap(Point2D(0, 0), fils, cols, this);
//	gO.push_back(map);
//
//	for (int i = 0; i < fils; i++) {
//		for (int j = 0; j < cols; j++) {
//			int n;
//			input >> n;
//			if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
//
//			if (n < 4) {
//				map->celdas[i][j] = (MapCell)n;
//				if (n == 2)++amountFood;
//			}
//			else  map->celdas[i][j] = Empty;
//		}
//	}
//
//	bar = new InfoBar(this, Textures[1], Textures[3]);
//	createNPositionate(input);
//}
//Bucle principal del juego que se encarga de actualizar las posiciones, puntuacion , perdida de vida y comprobar el estado del jugador.
void Game::run()
{
	SDL_Event event;
	int startTime, frameTime;

	while (!exit)
	{
		startTime = SDL_GetTicks();

		handleEvent(event, exit);

		stateMachine->currentState()->update();
		stateMachine->currentState()->render();
		//update();
		//render();

		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteración
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante

		//if (amountFood == 0)
		//{
		//	if(Current_Level<Levels.size()) changeLevel();
		//	else  hasWon = true;
		//}
	}

	/*if(hasSaved) cout << "Congratulations! You have saved cause you're a pussy. Hope you never come back.";
	else if (hasWon) cout << "You have won, go and fuck off";
	else if (!hasWon && lives <= 0) cout << "You have lost, you are so bad, you literally suck";
	else cout << " Hope you never come back.";*/
}
//Actualiza cada uno de los elementos del Juego: posicion, vidas y las colisiones entre el jugador y los fantasmas
void Game::update()
{
	stateMachine->currentState()->update();
}
//renderiza el mapa, con cada textura correspondiente en su lugar. Luego renderiza el jugador y la barra de HUD. 
void Game::render() 
{

	//todo esto seria del PlayState
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	stateMachine->currentState()->render();

	
	//estos valores hay que cambiarlos para que sean una referencia y no hacer el Update en el render
	

	SDL_RenderPresent(renderer);
}
//devolvemos el tipo de casilla en función de una posición dada
//int Game::getCellType(Point2D posPlayer) const
//{
//	return map->celdas[posPlayer.getY()][posPlayer.getX()];
//}

////resta en una unidad las vidas y devuelve si el jugador sigue vivo
//bool Game::restLife()
//{
//	lives--;
//	return lives > 0;
//}
////crea los fantasmas y el player dado un flujo de entrada y el numero de objetos
//void Game::createNPositionate(ifstream& input)
//{
//	int gameObjects;
//	input >> gameObjects;
//	if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
//					//no se incluye el mapa
//	for (int i = 0; i < gameObjects -1; i++) {
//		int n;
//		input >> n;
//		if (!input) throw FileFormatError("Format wrong. Data type unexpected.");
//		if (n == 9) {
//			player = new PacMan(input, this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT));
//			player->SetItList(gO.insert(gO.end(), player));
//		}
//		else if (n != 4) {
//			Ghost* newG = new Ghost(input, this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), n - 4);
//			newG->SetItList(gO.insert(gO.end(), newG));
//			Ghosts.push_back(newG);
//		}
//		else {
//			SmartGhost* newG = new SmartGhost(input, this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), Point2D(12, 1));
//			newG->SetItList(gO.insert(gO.end(), newG));
//			Ghosts.push_back(newG);
//		}
//	}
//}
////comprobamos si los fantasmas y el pac-man están en la misma posición y actuamos en consecuencia
//void Game::colissions(const SDL_Rect rect) const
//{
//	for (Ghost* g : Ghosts){		
//		SDL_Rect ghostRect = g->getDestRect();
//		if (SDL_HasIntersection(&rect, &ghostRect)){
//			if (player->GetEnergy() > 0 ) g->death();
//			else if (!player->GetRespawn()){
//				SmartGhost* fantasmita = dynamic_cast<SmartGhost*>(g);
//				if (fantasmita != NULL) if (fantasmita->getState() == Adult || fantasmita->getState() == Quarantine) player->death();
//				else player->death();
//			}
//		}
//	}
//}
////Comprobamos si un fantasma de tipo SmartGhost ha colisionado con otro fantasma, para asi reproducirse
//void Game::collisionGhost(const SDL_Rect rect, Ghost* ghost)
//{
//	SmartGhost* smart = dynamic_cast<SmartGhost*>(ghost);
//	if (smart != NULL){
//		for (Ghost* g : Ghosts){
//			SDL_Rect ghostRect = g->getDestRect();
//
//			if (!equalRect(rect, ghostRect) && SDL_HasIntersection(&rect, &ghostRect))
//				reproduce(smart, g);
//		}
//	}
//}
////Guarda cada uno de los GameObjects del juego, incluyendo las vidas y la puntuación.
//void Game::saveToFileGame()
//{
//	ofstream output;
//	string file = ".//matches//" + user + ".dat";
//	output.open(file);
//	if (!output.is_open()) throw FileNotFoundError("Can't find file" + user + ".dat");
//
//	output << lives << " " << points << endl;
//	map->saveToFile(output);
//
//	output << gO.size() << endl;
//
//	for (GameObject* gameOb : gO){
//		GameCharacter* gC = dynamic_cast<GameCharacter*>(gameOb);
//		if(gC != NULL)
//			gC->saveToFile(output);
//	}
//	output.close();
//}
////Metodo que recibe dos fantasmas, los analiza y si corresponde, se crea un nuevo fantasma dependiendo del tipo de los padres
//void Game::reproduce(SmartGhost* _father, Ghost* couple)
//{
//	//Comprobamos solo la madre porque anteriormente comprobamos que lo es el padre
//	bool freePos = false;
//	int i = 0;
//
//	while(i < 4 && !freePos){
//		freePos = tryMove(_father->getDestRect(), _father->getDir(i), _father->GetPos());
//		++i;
//	}
//
//	//Si no hay hueco, pues no se crea ningún fantasma
//	if (i < 4 && _father->getState() == Adult){
//		SmartGhost* mother = dynamic_cast<SmartGhost*>(couple);
//
//		if (mother !=NULL){
//			if (mother->getState() == Adult){
//				SmartGhost* newG = new SmartGhost(_father->GetPos() + _father->getDir(i), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), 4, Point2D(12,1));
//				newG->SetItList(gO.insert(gO.end(), newG));
//				Ghosts.push_back(newG);
//				//Pone a ambos padres en cuarentena
//				mother->setState(Quarantine);
//				_father->setState(Quarantine);
//			}
//		}
//		else{
//			//selecciona un color del padre random.
//			int select = (rand() % 3);
//
//			Ghost* newG = new Ghost(_father->GetPos() + _father->getDir(i), this, Textures[1], Point2D(OFFSET_WIDTH, OFFSET_HEIGHT), select);
//			newG->SetItList(gO.insert(gO.end(), newG));
//			Ghosts.push_back(newG);
//
//			_father->setState(Quarantine);
//		}
//	}
//}
////Dada una poscición y un n que hace referencia al tipo de celda, cambiamos el valor en el mapa
//void Game::setCell(int n, Point2D posPlayer)
//{
//	map->celdas[posPlayer.getY()][posPlayer.getX()] = (MapCell)n;
//}
//Menu de juego, carga de partida asociada al nombrel usuario
void Game::menu()
{
	cout << "Welcome to PacMan \nControls: Use directionals arrows to move | Press at any moment the key S to save | Quit closing the window |\nPlease, enter your user name: " << endl;
	user = "t";
	cin >> user;
	cout << "Want to load? Note: your user name is associated to your match file.\nY: 1 | N: 0" << endl;

	int op;
	do
	{
		cin >> op;
	} while (op != 1 && op != 0);

	//wantLoad = op;
}
//comprobamos que input está introduciendo el usuario y actuamos en consecuencia
void Game::handleEvent(SDL_Event& event, bool& exit)
{
	while (SDL_PollEvent(&event) && !exit) 
	{
		if (event.type == SDL_QUIT)
		{
			exit = true;
			cout << "Game has been closed.";
		}
		else if (event.type == SDL_KEYDOWN)
		{
			stateMachine->currentState()->handleEvents(event);

			SDL_Keycode key = event.key.keysym.sym;

			//if(key != SDLK_s)player->handleEvent(key);
			//else
			//{
			//	exit = true;
			//	hasSaved = true;
			//	saveToFileGame();
			//}
		}

	}
}
////Suma puntos
//void Game::SumaPuntos(int cantidad)
//{
//	points += cantidad;
//}
////Comprueba si uno de los personajes ha salido de pantalla y le permite transportarse al otro lado
//void Game::ToroidalPos(Point2D& pos)
//{
//	SDL_Rect mapRect = map->getDestRect();
//
//	if (pos.getX() + OFFSET_WIDTH > mapRect.x + map->width*OFFSET_WIDTH) pos = Point2D(mapRect.x, pos.getY());
//	else if (pos.getX() < mapRect.x) 
//		pos = Point2D(mapRect.x + map->width * OFFSET_WIDTH - OFFSET_WIDTH, pos.getY());
//	else if (pos.getY() > mapRect.y + map->width*OFFSET_HEIGHT) 
//		pos = Point2D(pos.getX(), mapRect.y+OFFSET_HEIGHT);
//	else if (pos.getY() < mapRect.y + OFFSET_HEIGHT) pos = Point2D(pos.getX(), mapRect.y + map->width * OFFSET_HEIGHT);
//}
////Coloca a cada fantasma como "comible" o no
//void Game::setGhostsEdables(bool eda)
//{
//	 for (Ghost* g : Ghosts) g->setEdable(eda);
//}
////Comprueba si el siguiente pixel es válido para moverse
//bool Game::tryMove(SDL_Rect rect, Vector2D dir, Point2D Pos)
// {
//	 SDL_Rect newRect;
//	 Point2D newPos = Pos + dir;
//	 newRect.w = rect.w;
//     newRect.h = rect.h;
//		
//	 newRect.x = newPos.getX();
//	 newRect.y = newPos.getY();
//
//	 //Si no ha intersectado (false) se nega para que pueda avanzar.
//	 return !map->intersectWall(newRect);
// }
////Convierte las coordenadas de las celdas a pixeles
//void Game::mapCoordToSDLPoint(Point2D old, Point2D& newP)
// {
//	 newP.setX(old.getX()* OFFSET_WIDTH);
//	 newP.setY(old.getY() * OFFSET_HEIGHT + OFFSET_HEIGHT);
// }
////Convierte las coordenadas de pixeles a celdas del mapa
//void Game::SDLPointToMapCoords(Point2D old, Point2D& newP)
// {
//	 newP.setX(old.getX() / OFFSET_WIDTH);
//	 newP.setY((old.getY() - OFFSET_HEIGHT ) / OFFSET_HEIGHT);
// }
////almacena los fantasmas que han muerto para luego eliminarlos de la escena
//void Game::borraFantasma(list<GameObject*>::iterator it, Ghost* fantasma)
// {
//	 Ghosts.remove(fantasma);
//	 objectsToErase.push_back(it);
// }
////Borra los objetos pendientes que estan muertos en la escena
//void Game::Borra()
// {
//	 for (auto gameOb : objectsToErase)
//	 {
//		 delete *gameOb; //es un iterador y hay que eliminar el objeto de la lista
//		 //erase elimina el Nodo donde esta ubicado el iterador
//		 gO.erase(gameOb);
//	 }
//	 objectsToErase.clear(); //borrar iteradores de la lista
// }
//Cambia el nivel en caso de que haya terminado de consumir todas las celdas de comida. Reinicia la puntuación pero mantiene las vidas.
//void Game::changeLevel()
// {
//	 int currentLifes = lives;
//
//	 for (GameObject* gameOb : gO) delete gameOb;
//
//	 Ghosts.clear();
//	 gO.clear();
//
//	 Current_Level++;
//	 points = 0;
//
//	 load(currentLifes);
//}
