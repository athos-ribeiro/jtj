#include "scorescreen.h"
#include "sdlutil.h"

ScoreScreen::ScoreScreen(string scoreFontFileName, scoreFontSize)
{
    armario = SDLUtil::loadImage("resources/armario.png");
    scoreTextColor.r = 255;
    scoreTextColor.g = 255;
    scoreTextColor.b = 255;
    scoreFont = TTF_OpenFont (scoreFontFileName.c_str(), scoreFontSize);

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
ScoreScreen::updateSelf()
{
    scorePoints ++;
    boxLeft --;

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
    SDLUtil::applySurface (0, 0, this->scoreMessage, this->armario);
    SDLUtil::applySurface (50, 0, this->boxMessage, this->armario);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET, ScoreScreen::SCORE_Y_OFFSET, this->armario, surface);
}