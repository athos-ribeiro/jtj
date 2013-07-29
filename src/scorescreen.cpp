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
    this->scoreFont = TTF_OpenFont ("resources/HanaleiRegular.ttf", 40);

	this->scorePoints = 0;
    sprintf(this->scoreString, "Score: %5d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);

    this->lineLeft = 99;
    sprintf(this->lineString, "Lines left: %d", this->lineLeft);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->lineString, this->scoreTextColor);
}

ScoreScreen::~ScoreScreen()
{
    TTF_CloseFont (scoreFont);
    SDL_FreeSurface (armario);
    SDL_FreeSurface (scoreMessage);
}

void
ScoreScreen::lines(int numero)
{
    this->lineLeft = numero;
}

void
ScoreScreen::scoring(int value)
{
    this->scorePoints = value;
}


int
ScoreScreen::getLine()
{
    return this->lineLeft;
}

int
ScoreScreen::getScorePoints()
{
    return this->scorePoints;
}

void
ScoreScreen::popLine()
{
    this->lineLeft --;
    return ;
}

void
ScoreScreen::increaseScore(int value)
{
    this->scorePoints += value;
    return ;
}

void
ScoreScreen::updateSelf()
{
    sprintf(this->scoreString, "Score: %6d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);

    sprintf(this->lineString, "Line left: %2d", this->lineLeft);
    this->boxMessage = TTF_RenderText_Solid (this->scoreFont, this->lineString, this->scoreTextColor);

    return ;
}

void
ScoreScreen::drawSelf(SDL_Surface *surface)
{
    updateSelf();
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET, ScoreScreen::SCORE_Y_OFFSET, this->armario, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 25, this->scoreMessage, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 75, this->boxMessage, surface);
}