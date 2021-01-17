#pragma once
#include <string>

#include <array>;
#include "Ghost.h";
#include "GameState.h";
#include "GameMap.h";
#include "PacMan.h";
#include "InfoBar.h";
#include "SmartGhost.h";

using namespace std;


const int NUM_LEVELS = 6;

class PlayState : public GameState
{

	int fils, cols;
	int amountFood = 0; //comida restante en el juego
	int points;  //Puntuacion del juego 
	int Current_Level; //Nivel actual
	int lives;

	bool hasWon;//Controladores del juego
	
	//ARRAY DE NIVELES
	const array<string, NUM_LEVELS> Levels = { "levels/level01.dat", "levels/level02.dat", "levels/level03.dat" , "levels/level04.dat", "levels/level05.dat", "levels/test1.dat" };
	

	list<Ghost*> Ghosts;
	list<list<GameObject*>::iterator> objectsToErase;

	GameMap* map;			//Puntero al mapa
	PacMan* player;			//Puntero al jugador
	InfoBar* bar;			//Puntero al HUD

public:
	PlayState(SDLApplication* game, TextureManager* tM);
	PlayState(SDLApplication* game, TextureManager* tM, ifstream& input);
	~PlayState();

	void load(int lifes);
	void CreateSmartGhost(int j, int i, int n);
	void CreateGhost(int j, int i, int n);
	void CreatePlayer(int j, int i);
	void FoodEaten() { --amountFood; };
	
	void Borra();
	virtual void update();
	virtual void render();
	virtual bool handleEvents(SDL_Event& event);

	bool restLife();
	void changeLevel();
	void SumaPuntos(int cantidad);
	void ToroidalPos(Point2D& pos);
	void setGhostsEdables(bool eda);
	void setCell(int n, Point2D posPlayer);
	void createNPositionate(ifstream& input);
	void colissions(const SDL_Rect rect)const;
	void mapCoordToSDLPoint(Point2D old, Point2D& newP);
	void SDLPointToMapCoords(Point2D old, Point2D& newP);
	void collisionGhost(const SDL_Rect rect, Ghost* ghost);
	bool tryMove(SDL_Rect rect, Vector2D dir, Point2D newPos);
	void borraFantasma(list<GameObject*>::iterator it, Ghost* fantasma);
	void saveToFileGame(int code);
	bool loadMatch(ifstream& input);

private:
	void reproduce(SmartGhost* father, Ghost* mother);
	bool equalRect(SDL_Rect r1, SDL_Rect r2) const { return r1.x == r2.x && r1.y == r2.y; };

	static void Pausa(SDLApplication* game);

#pragma region GETTERS
	int getCols() const { return cols; }
	int getFils() const { return fils; }
	int GetLives() const { return lives; }
	bool GetRunning() const { return !hasWon && lives > 0; }
	
public:
	Point2D PlayerPos() const { return player->GetPos(); }
	int getWindowWidth() const;
	int getWindowHeight() const;
	int getGameFrameRate() const;
	int getCellType(Point2D posPlayer) const;
#pragma endregion
};

