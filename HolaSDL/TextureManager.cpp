#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer)
{
	//Inicilizamos las texturas
	for (int i = 0; i < Textures.size(); i++)
		Textures[i] = new Texture(renderer, TEXTURE_ATRIB[i].filename, TEXTURE_ATRIB[i].numRows, TEXTURE_ATRIB[i].numCols);
}
TextureManager::~TextureManager()
{
	for (Texture* t : Textures) delete t;
}
//Devuelve la textura relacionada con el Enum y el entero de entrada
Texture* TextureManager::getTexture(TextureName t)
{
	return Textures[(int)t];
}
