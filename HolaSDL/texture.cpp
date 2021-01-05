#include "texture.h"
#include <iostream>

using namespace std;
//Libera la textura y deja el puntero a nulo 
void Texture::Free() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}
//Carga una textura
void Texture::load(string filename, uint nRows, uint nCols) {

	SDL_Surface* tempSurface = IMG_Load(filename.c_str());

	if (tempSurface == nullptr)
		throw SDLError("Error loading surface from" + filename);

	Free();

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	if (texture == nullptr) 
		throw SDLError("Error loading surface from" + filename);
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;

	SDL_FreeSurface(tempSurface);
}
//Renderiza una textura
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}
//Renderiza una frame "recortando" una zona indicada la Textura
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}
