#ifndef SCORESCREEN_h
#define SCORESCREEN_h

class ScoreScreen
{
public:
	ScoreScreen(string scoreFontFileName = "resources/HanaleiRegular.ttf", scoreFontSize = 30);
	~ScoreScreen();
	void update();
	void drawSelf();

private:

	SDL_Surface *armario;
    TTF_Font *scoreFont;
    SDL_Surface *scoreMessage;
    SDL_Surface *boxMessage;
    SDL_Color scoreTextColor;
    char scoreString[13];
    char boxString[13];
    int scorePoints;
    int boxLeft;

    static const int SCORE_WIDTH = 282;
    static const int SCORE_HEIGHT = 456;
    static const int SCORE_X_OFFSET = 506;
    static const int SCORE_Y_OFFSET = 10;



};

#endif