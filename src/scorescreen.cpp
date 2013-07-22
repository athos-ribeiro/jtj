#include "scorescreen.h"
#include "sdlutil.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <string>

ScoreScreen::ScoreScreen()
{
    armario = SDLUtil::loadImage("resources/armario.png");
    scoreTextColor.r = 255;
    scoreTextColor.g = 255;
    scoreTextColor.b = 255;
    scoreFont = TTF_OpenFont ("resources/HanaleiRegular.ttf", 42);

	scorePoints = 0;
    sprintf(scoreString, "Score: %5d", scorePoints);
    scoreMessage = TTF_RenderText_Solid (scoreFont, scoreString, scoreTextColor);

    boxLeft = 99;
    sprintf(this->boxString, "Box left: %2d", this->boxLeft);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->boxString, this->scoreTextColor);
}

ScoreScreen::~ScoreScreen()
{
    TTF_CloseFont (scoreFont);
    SDL_FreeSurface (armario);
    SDL_FreeSurface (scoreMessage);
}

int
ScoreScreen::getBox()
{
    return boxLeft;
}

int
ScoreScreen::getScorePoints()
{
    return scorePoints;
}

int
ScoreScreen::popBox()
{
    boxLeft --;
    return updateSelf();
}

int
ScoreScreen::increaseScore(int value)
{
    scorePoints += value;
    return updateSelf();
}

int
ScoreScreen::updateSelf()
{
    if (boxLeft <= 0 || scorePoints > 99999)
    {
    	return 1;
    }

    sprintf(this->scoreString, "Score: %5d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);

    sprintf(this->boxString, "Box left: %2d", this->boxLeft);
    this->boxMessage = TTF_RenderText_Solid (this->scoreFont, this->boxString, this->scoreTextColor);

    return 0;
}

void
ScoreScreen::drawSelf(SDL_Surface *surface)
{
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET, ScoreScreen::SCORE_Y_OFFSET, this->armario, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 25, this->scoreMessage, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 75, this->boxMessage, surface);
}