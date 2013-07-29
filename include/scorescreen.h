#ifndef SCORESCREEN_h
#define SCORESCREEN_h

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <string>

class ScoreScreen
{
public:
    ScoreScreen();
    ~ScoreScreen();
    void drawSelf(SDL_Surface *surface);
    int getLine();
    int getScorePoints();
    void popLine();
    void increaseScore(int value);
    void lines(int numero);
    void scoring(int value);

private:

    void updateSelf();

    SDL_Surface *armario;
    TTF_Font *scoreFont;
    SDL_Surface *scoreMessage;
    SDL_Surface *boxMessage;
    SDL_Color scoreTextColor;
    char scoreString[30];
    char lineString[30];
    int scorePoints;
    int lineLeft;

    static const int SCORE_WIDTH = 282;
    static const int SCORE_HEIGHT = 456;
    static const int SCORE_X_OFFSET = 506;
    static const int SCORE_Y_OFFSET = 10;
};

#endif