#ifndef GAME_H_
#define GAME_H_

#include <sdlutil.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "level.h"
#include "timer.h"
#include "jack.h"
#include "label.h"
#include "initscreen.h"
#include "pausescreen.h"
#include "gameoverscreen.h"
#include <string>
#include "scorescreen.h"
#include <stdlib.h>
#include "optionsscreen.h"

class Game {
    public:
        void init();
        void loop();
        void shutdown();

    private:
        Level* level;
        SDL_Surface *screen;
        SDL_Event event;
        Jack* jack;
        Timer frameTime;

        ScoreScreen* score;

        InitScreen* initScreen;
        InitScreen* wonScreen;
        PauseScreen* pauseScreen;
        GameOverScreen* gameOverScreen;
        OptionsScreen* optionsScreen;

        Label* labelPlay;
        Label* labelOptions;
        Label* labelQuit;

        Label* labelMute;
        Label* labelLoad;
        Label* labelBack;

        static const int SCREEN_WIDTH = 854;
        static const int SCREEN_HEIGHT = 480;
        static const int SCREEN_BPP = 32;

        static const int SCREEN_FPS = 60;

        float FRAME_MILISECOND;

        bool quitGame;
        bool quitLevel;
        bool pauseLevel;
        bool gameOver;
        bool gameWon;
        int linesDeleted;
        int maxLevelLines;
        int actualLevel;

        void wonGameScreen();
        void showOptionsScreen();
        void gameOvering();
        void gameOverScreenDraw();
        void gameOverScreenLoop();
        void pausingLevel();
        void pauseScreenDraw();
        void pauseScreenLoop();
        void initializingScreen();
        void initScreenDraw();
        void initScreenLoop();
        void initGUI();
        void closeGUI();
        void loadCommonResources();
        void releaseCommonResources();
        void loadProfile();
        void saveProfile();
        void updateTimeStep();
        int checkIfSkip();
        void handle_event_mouse_button_up (SDL_Event& event);
        void handle_event_mouse_button_down (SDL_Event& event);
        void handle_event_keydown (SDL_Event& event);
        void handle_event_keyup (SDL_Event& event);
        void handle_event_type (SDL_Event& event);
        void handleEvents();
        void runAI();
        void runPhysics();
        void update();
        void recieveNetworkData();
        void sendNetworkData();
        void draw();
        void loadLevel();
        void releaseLevel();
        bool isGameFinished();
        bool isLevelFinished();
};

#endif
