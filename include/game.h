#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifndef GAME_H_
#define GAME_H_

class Game {
    public:
        void init();
        void loop();
        void shutdown();

    private:
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
        static const int SCREEN_BPP = 32;

        SDL_Surface *screen;

        void initGUI();
        void closeGUI();
        void loadCommonResources();
        void releaseCommonResources();
        void loadProfile();
        void saveProfile();
        void updateTimeStep();
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
