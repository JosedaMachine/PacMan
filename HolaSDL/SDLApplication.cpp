#include "SDLApplication.h"
#include <ctime>
SDLApplication::SDLApplication()
{
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
SDLApplication::~SDLApplication()
{
	delete stateMachine;
	delete tM;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
//Bucle principal del juego que se encarga de actualizar las posiciones, puntuacion , perdida de vida y comprobar el estado del jugador.
void SDLApplication::run()
{
	SDL_Event event;
	int startTime, frameTime;

	while (!exit)
	{
		startTime = SDL_GetTicks();

		handleEvent(event, exit);
		//Actualiza cada uno de los elementos del Juego: posicion, vidas y las colisiones entre el jugador y los fantasmas
		stateMachine->currentState()->update();
		render();

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
//renderiza el mapa, con cada textura correspondiente en su lugar. Luego renderiza el jugador y la barra de HUD. 
void SDLApplication::render() 
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	stateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}
//Menu de juego, carga de partida asociada al nombrel usuario
void SDLApplication::menu()
{
	cout << "Welcome to PacMan \nControls: Use directionals arrows to move | Press at any moment the key S to save | Quit closing the window |\nPlease, enter your user name: " << endl;
	//user = "t";
	//cin >> user;
	cout << "Want to load? Note: your user name is associated to your match file.\nY: 1 | N: 0" << endl;

	int op;
	do
	{
		cin >> op;
	} while (op != 1 && op != 0);

	//wantLoad = op;
}//tengo la idea de que cuando queramos pausar el juego, si estamos en PlayState y le damos a scape, llamamos a un metodo de Game que haga un push de PauseMenu y que si le da a resume, se haga un pop del PauseMenu y se continue ejecutando el PLayState
void SDLApplication::ChangeState(States s)
{
	switch (s)
	{
	case Menu:
		stateMachine->changeState(new MainMenuState(this, tM));
		break;
	case Play:
		//resume arreglo
		stateMachine->changeState(new PlayState(this, tM));
		break;
	case Pause:
		stateMachine->changeState(new PauseState(this, tM));
		break;
	case End:
		stateMachine->changeState(new EndState(this, tM));
		break;
	default:
		break;
	}
}
//comprobamos que input está introduciendo el usuario y actuamos en consecuencia
void SDLApplication::handleEvent(SDL_Event& event, bool& exit)
{
	while (SDL_PollEvent(&event) && !exit) 
	{
		if (event.type == SDL_QUIT)
		{
			exit = true;
			cout << "Game has been closed.";
		}
		else
		{
			GameState* current = stateMachine->currentState();

			current->handleEvents(event);

			//SDL_Keycode key = event.key.keysym.sym;

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

void SDLApplication::PauseGame()
{
	stateMachine->pushState(new PauseState(this,tM));
}

void SDLApplication::ResumeGame()
{
	stateMachine->popState();
}

void SDLApplication::SaveGame(int codeNumber)
{
	stateMachine->popState();

	PlayState* actual = static_cast<PlayState*>(stateMachine->currentState());

	actual->saveToFileGame(codeNumber);
	exit = true;
}

void SDLApplication::LoadGame(int codeNumber)
{
	string file = ".//matches//" + to_string(codeNumber) + ".dat";

	PlayState* pS = new PlayState(this, tM, file);
	stateMachine->popState();
	stateMachine->pushState(pS);

}

int SDLApplication::askCodeNumber()
{
	cout << "Please enter your code number. Notice you will have to use it to load this match";
	int code;

	do
	{
		cin >> code;
	} while (code<0);

	return code;
}
