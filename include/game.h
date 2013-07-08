#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "level.h"
#include "timer.h"
#include "jack.h"

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

        static const int SCREEN_WIDTH = 854;
        static const int SCREEN_HEIGHT = 480;
        static const int SCREEN_BPP = 32;

        static const int SCREEN_FPS = 60;

        float FRAME_MILISECOND;

        // Whether the game and/or the level is finished
        bool quitGame;
        bool quitLevel;

        void initGUI();
        void closeGUI();
        void loadCommonResources();
        void releaseCommonResources();
        void loadProfile();
        void saveProfile();
        void updateTimeStep();

        //Whether the frame will skip or not. If it doesn't, sleep until FRAME_MILISECOND
        int checkIfSkip();

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
