#pragma once
#include "texture.h";
#include <array>;

const int NUM_TEXTURES = 12;
enum TextureName { WallMap, Characters, Food, Digits, PowerUp, exitButton, mainButton,	playButton , saveButton, resumeButton, loadButton, Title};
class TextureManager
{
private:
	struct TextureAtributes { string filename; int numRows; int numCols; };
	//ARRAY ESTATICO DE ATRIBUTOS DE TEXTURAS
	const TextureAtributes TEXTURE_ATRIB[NUM_TEXTURES] = { {"../images/wall3.png", 1, 1}, {"../images/characters.png", 4, 14} , {"../images/food2.png", 1, 1}, 
			{"../images/digits.jpeg", 3, 4}, {"../images/burguer.png", 1, 1},{"../images/exit.png", 1, 2}, {"../images/main.png", 1, 2}, {"../images/play.png", 1, 2}, {"../images/save.png", 1, 2},{"../images/resume.png", 1, 2}, {"../images/load.png", 1, 2}, {"../images/title.png", 1, 1} };
	//ARRAY DE NIVELES
	array<Texture*, NUM_TEXTURES> Textures;
public:
	TextureManager(SDL_Renderer* renderer);
	~TextureManager();
	Texture* getTexture(TextureName t);
};

