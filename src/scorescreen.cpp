#include "scorescreen.h"
#include "sdlutil.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

using namespace std;

ScoreScreen::ScoreScreen()
{
    this->armario = SDLUtil::loadImage("resources/armario.png");
    this->scoreTextColor.r = 255;
    this->scoreTextColor.g = 255;
    this->scoreTextColor.b = 255;
    this->scoreFont = TTF_OpenFont ("resources/HanaleiRegular.ttf", 42);

	this->scorePoints = 0;
    sprintf(this->scoreString, "Score: %5d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);

    this->boxLeft = 99;
    sprintf(this->boxString, "Box left: %2d", this->boxLeft);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->boxString, this->scoreTextColor);
}

ScoreScreen::~ScoreScreen()
{
    TTF_CloseFont (scoreFont);
    SDL_FreeSurface (armario);
    SDL_FreeSurface (scoreMessage);
}

void
ScoreScreen::boxes(int numero)
{
    this->boxLeft = numero;
}

void
ScoreScreen::scoring(int value)
{
    this->scorePoints = value;
}


int
ScoreScreen::getBox()
{
    return this->boxLeft;
}

int
ScoreScreen::getScorePoints()
{
    return this->scorePoints;
}

int
ScoreScreen::popBox()
{
    cout << "Box" << endl;
    this->boxLeft --;
    cout << "Minus" << endl;
    return updateSelf();
}

int
ScoreScreen::increaseScore(int value)
{
    cout << "Score" << endl;
    this->scorePoints += value;
    cout << "Plus" << endl;
    return updateSelf();
}

int
ScoreScreen::updateSelf()
{
    if (this->boxLeft <= 0 || this->scorePoints > 99999)
    {
    	return 1;
    }
    cout << "Is" << endl;
    sprintf(this->scoreString, "Score: %5d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);
    cout << "This" << endl;

    sprintf(this->boxString, "Box left: %2d", this->boxLeft);
    this->boxMessage = TTF_RenderText_Solid (this->scoreFont, this->boxString, this->scoreTextColor);
    cout << "Working?" << endl;

    return 0;
}

void
ScoreScreen::drawSelf(SDL_Surface *surface)
{
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET, ScoreScreen::SCORE_Y_OFFSET, this->armario, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 25, this->scoreMessage, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 75, this->boxMessage, surface);
}