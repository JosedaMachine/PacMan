#pragma once
#include "texture.h";
#include <array>;

const int NUM_TEXTURES = 10;
enum TextureName { WallMap, Characters, Food, Digits, PowerUp, exitButton, mainButton,	playButton , restartButton, resumeButton};
class TextureManager
{
private:
	struct TextureAtributes { string filename; int numRows; int numCols; };
	//ARRAY ESTATICO DE ATRIBUTOS DE TEXTURAS
	const TextureAtributes TEXTURE_ATRIB[NUM_TEXTURES] = { {"../images/wall3.png", 1, 1}, {"../images/characters.png", 4, 14} , {"../images/food2.png", 1, 1}, 
			{"../images/digits.jpeg", 3, 4}, {"../images/burguer.png", 1, 1},{"../images/exit.png", 1, 3}, {"../images/main.png", 1, 3}, {"../images/play.png", 1, 3}, {"../images/restart.png", 1, 3},{"../images/resume.png", 1, 3} };
	//ARRAY DE NIVELES
	array<Texture*, NUM_TEXTURES> Textures;
public:
	TextureManager(SDL_Renderer* renderer);
	~TextureManager();
	Texture* getTexture(TextureName t);

};

