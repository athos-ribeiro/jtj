#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "level.h"
#include "timer.h"
#include "jack.h"
#include "label.h"
#include "initscreen.h"
#include "pausescreen.h"

#ifndef GAME_H_
#define GAME_H_

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

        InitScreen* initScreen;
        PauseScreen* pauseScreen;

        Label* labelPlay;
        Label* labelOptions;
        Label* labelQuit;

        static const int SCREEN_WIDTH = 854;
        static const int SCREEN_HEIGHT = 480;
        static const int SCREEN_BPP = 32;

        static const int SCREEN_FPS = 60;

        float FRAME_MILISECOND;

        bool quitGame;
        bool quitLevel;
        bool pauseLevel;

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
