#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* game, TextureManager* tM) : GameState(game, tM)
{
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

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::play(SDLApplication* game)
{
	game->ChangeState(Play);
}

void MainMenuState::render()
{
	renderTitle();
	GameState::render();
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::renderTitle()
{
	int multiplier = 5;

	SDL_Rect destRect;
	destRect.w = title->getW() / multiplier;
	destRect.h = title->getH() / multiplier;
	destRect.x = OFFSET_WIDTH / 2 - destRect.w/2;
	destRect.y = OFFSET_HEIGHT / 3 - destRect.h;
	title->render(destRect);
}

//bool MainMenuState::handleEvents(SDL_Event& event)
//{
//	return GameState::handleEvents(event);
//}
