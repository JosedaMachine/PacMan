#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* game, TextureManager* tM) : GameState(game, tM)
{
	bG = tM->getTexture(Bg);
	title = tM->getTexture(Title);

	Texture* start = tM->getTexture(playButton); //Guardamos la textura
	//Para que aparezca en mitad de pantalla
	int multiplier = 2;
	//se puede pillar el numero de rows y cols de cada textura 
	Point2D pos = Point2D(OFFSET_WIDTH / 2 - (start->getW()/ (4* multiplier)) , OFFSET_HEIGHT / 2 - (start->getH() / multiplier));
	//Botones
	#pragma region Start
		MenuButton* newBut = new MenuButton(pos,game, start, start->getW()/(2* multiplier), start->getH()/ multiplier, play);
		events.push_back(newBut);
		gO.push_back(newBut);
	#pragma endregion

    #pragma region Load
	Texture* load = tM->getTexture(loadButton); //Guardamos la textura
	//Para que aparezca en mitad de pantalla
	//int multiplier = 2;	//se puede pillar el numero de rows y cols de cada textura 
	Point2D posload = Point2D(OFFSET_WIDTH / 2 - (load->getW() / (4 * multiplier)), OFFSET_HEIGHT / 1.5 - (load->getH() / multiplier));	

	MenuButton* newButLoad = new MenuButton(posload, game, load, load->getW() / (2 * multiplier), load->getH() / multiplier, Load);
	events.push_back(newButLoad);
	gO.push_back(newButLoad);
    #pragma endregion
}
//Empieza el estado del juego
void MainMenuState::play(SDLApplication* game)
{
	game->ChangeState(Play);
}
//Carga una partida dado un codigo numerico
void MainMenuState::Load(SDLApplication* game)
{
	int code = game->askCodeNumber();
	game->LoadGame(code);
}
//renderiza los botones y el fondo 
void MainMenuState::render()
{
	renderTitleNBg();
	GameState::render();
}
//Renderiza el fondo y el titulo
void MainMenuState::renderTitleNBg()
{
	SDL_Rect destRect;
	int multiplier = 3;

	destRect.w = bG->getW()/ multiplier;
	destRect.h = bG->getH() /multiplier;
	destRect.x = OFFSET_WIDTH / 2 - destRect.w / 2;
	destRect.y = 0;

	bG->render(destRect);

	multiplier = 5;
	destRect.w = title->getW() / multiplier;
	destRect.h = title->getH() / multiplier;
	destRect.x = OFFSET_WIDTH / 2 - destRect.w/2;
	destRect.y = OFFSET_HEIGHT / 3 - destRect.h;
	title->render(destRect);
}

