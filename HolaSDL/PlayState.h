#pragma once
#include <string>
#include "texture.h";
#include <array>;
#include "Ghost.h";
#include "GameState.h";
#include "GameMap.h";
#include "PacMan.h";
#include "InfoBar.h";
#include "SmartGhost.h";

using namespace std;

const int NUM_TEXTURES = 5;
const int NUM_LEVELS = 6;
enum TextureName { WallMap, Characters, Food, Digits, PowerUp };
class PlayState : public GameState
{
	int fils, cols;
	int amountFood; //comida restante en el juego
	int points;  //Puntuacion del juego 
	int Current_Level; //Nivel actual
	int lives;

	struct TextureAtributes { string filename; int numRows; int numCols; };
	//ARRAY DE NIVELES
	const array<string, NUM_LEVELS> Levels = { "levels/level01.dat", "levels/level02.dat", "levels/level03.dat" , "levels/level04.dat", "levels/level05.dat", "levels/test1.dat" };
	//ARRAY ESTATICO DE ATRIBUTOS DE TEXTURAS
	const TextureAtributes TEXTURE_ATRIB[NUM_TEXTURES] = { {"../images/wall3.png", 1, 1}, {"../images/characters.png", 4, 14} , {"../images/food2.png", 1, 1}, {"../images/digits.jpeg", 3, 4}, {"../images/burguer.png", 1, 1} };
	//ARRAY DE NIVELES
	array<Texture*, NUM_TEXTURES> Textures;

	list<Ghost*> Ghosts;
	list<list<GameObject*>::iterator> objectsToErase;


	GameMap* map;			//Puntero al mapa
	PacMan* player;			//Puntero al jugador
	InfoBar* bar;			//Puntero al HUD
public:
	void load(int lifes);
	void FoodEaten() { --amountFood; };
	Texture* getTexture(TextureName t);
	void Borra();
	bool restLife();
	void changeLevel();
	void SumaPuntos(int cantidad);
	void ToroidalPos(Point2D& pos);
	void setGhostsEdables(bool eda);
	void setCell(int n, Point2D posPlayer);
	void createNPositionate(ifstream& input);
	void colissions(const SDL_Rect rect)const;
	void handleEvent(SDL_Event& event, bool& exit);
	void mapCoordToSDLPoint(Point2D old, Point2D& newP);
	void SDLPointToMapCoords(Point2D old, Point2D& newP);
	void collisionGhost(const SDL_Rect rect, Ghost* ghost);
	bool tryMove(SDL_Rect rect, Vector2D dir, Point2D newPos);
	void borraFantasma(list<GameObject*>::iterator it, Ghost* fantasma);


private:
	void saveToFileGame();
	void reproduce(SmartGhost* father, Ghost* mother);
	bool equalRect(SDL_Rect r1, SDL_Rect r2) const { return r1.x == r2.x && r1.y == r2.y; };
	void loadMatch(ifstream& input);

#pragma region GETTERS
	int getCols() const { return cols; }
	int getFils() const { return fils; }
	int GetLives() const { return lives; }
	Point2D PlayerPos() const { return player->GetPos(); }
	int getCellType(Point2D posPlayer) const;
#pragma endregion
};

