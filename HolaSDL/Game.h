#pragma once
#include <fstream>
#include <array>
#include <string>

#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"

#include "GameMap.h"
#include "texture.h"
#include "PacMan.h"
#include "Ghost.h"
#include "SmartGhost.h"
#include "Vector2D.h"
#include "InfoBar.h"
#include "checkML.h"

#include "GameStateMachine.h"
#include "MainMenuState.h"


//const int NUM_TEXTURES = 5; 
//const int NUM_LEVELS = 6;

const int FRAME_RATE = 5;

//Tama�o en X e Y de la pantalla
const uint WIN_WIDTH = 700;
const uint WIN_HEIGHT = 700;

//enum TextureName { WallMap, Characters, Food, Digits, PowerUp };

class Game
{
private:

	SDL_Window* window = nullptr; //Puntero a la ventana
	SDL_Renderer* renderer = nullptr;  //puntero a renderer
	//int fils, cols; 
	//int amountFood; //comida restante en el juego
	//int points;  //Puntuacion del juego 
	//int Current_Level; //Nivel actual
	string user;
	//int lives;

	GameStateMachine* stateMachine;

	bool exit, hasWon, hasSaved, wantLoad; //Controladores del juego
		
	int OFFSET_WIDTH; //Tama�o de cada texturas
	int OFFSET_HEIGHT; //Tama�o de cada texturas
	//puedo acceder a sus parametros aunque sean privados

	////Tipos de texturas
	////STRUCT CON LOS ATRIBUTOS DE CADA TEXTURA
	//struct TextureAtributes { string filename; int numRows; int numCols; };
	////ARRAY DE NIVELES
	//const array<string, NUM_LEVELS> Levels = { "levels/level01.dat", "levels/level02.dat", "levels/level03.dat" , "levels/level04.dat", "levels/level05.dat", "levels/test1.dat" };
	////ARRAY ESTATICO DE ATRIBUTOS DE TEXTURAS
	//const TextureAtributes TEXTURE_ATRIB[NUM_TEXTURES] = { {"../images/wall3.png", 1, 1}, {"../images/characters.png", 4, 14} , {"../images/food2.png", 1, 1}, {"../images/digits.jpeg", 3, 4}, {"../images/burguer.png", 1, 1} };
	////ARRAY DE NIVELES
	//array<Texture*, NUM_TEXTURES> Textures;
	////ARRAY DE FANTASMAS
	//list<Ghost*> Ghosts;
	//list<GameObject*>gO;
	//list<list<GameObject*>::iterator> objectsToErase;

	//GameMap* map;			//Puntero al mapa
	//PacMan* player;			//Puntero al jugador
	//InfoBar* bar;			//Puntero al HUD


public:
	Game();
	~Game();

	//Texture* getTexture(TextureName t);
	//void load(int lifes);
	void run();
	void menu();
	//void Borra();
	void render();
	void update();
	//bool restLife();
	//void changeLevel();
	//void SumaPuntos(int cantidad);
	//void ToroidalPos(Point2D& pos);
	//void setGhostsEdables(bool eda);
	//void FoodEaten() { --amountFood; };
	/*void setCell(int n, Point2D posPlayer);
	void createNPositionate(ifstream& input);*/
	/*void colissions(const SDL_Rect rect)const;*/
	void handleEvent(SDL_Event& event, bool& exit);
	/*void mapCoordToSDLPoint(Point2D old, Point2D& newP);
	void SDLPointToMapCoords(Point2D old, Point2D& newP);*/
	/*void collisionGhost(const SDL_Rect rect, Ghost* ghost);
	bool tryMove(SDL_Rect rect, Vector2D dir, Point2D newPos);
	void borraFantasma(list<GameObject*>::iterator it, Ghost* fantasma);*/

	#pragma region GETTERS
	/*int getCols() const { return cols; }
	int getFils() const { return fils; }
	int GetLives() const { return lives; }*/
	/*int getCellType(Point2D posPlayer) const;*/
	int getWidth() const { return WIN_WIDTH; }
	int getHeight() const { return WIN_HEIGHT; }
	int getFrameRate() const { return FRAME_RATE; }
	int getOffsetWidth() const { return OFFSET_WIDTH;}
	int getOffsetHeight() const { return OFFSET_HEIGHT;}
	//Point2D PlayerPos() const { return player->GetPos(); }
	#pragma endregion

	
private:
	//void saveToFileGame();
	/*void loadMatch(ifstream& input);*/
	//void reproduce(SmartGhost* father, Ghost* mother);
	//bool equalRect(SDL_Rect r1, SDL_Rect r2) const { return r1.x == r2.x && r1.y == r2.y; };

};