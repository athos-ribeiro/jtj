#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "level.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
    public:
        void init();
        void loop();
        void shutdown();

    private:
        Level* level;

        static const int SCREEN_WIDTH = 854;
        static const int SCREEN_HEIGHT = 480;
        static const int SCREEN_BPP = 32;

        // Whether the game and/or the level is finished
        int quit_game;
        int quit_level;

        SDL_Surface *screen;

        SDL_Event event;

        void initGUI();
        void closeGUI();
        void loadCommonResources();
        void releaseCommonResources();
        void loadProfile();
        void saveProfile();
        void updateTimeStep();
        void handle_event_keydown (SDL_Event& event);
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
