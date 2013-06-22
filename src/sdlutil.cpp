#include "sdlutil.h"
#include <string>
#include <SDL/SDL_image.h>

using namespace std;

SDL_Surface *SDLUtil::loadImage(string filename) {
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());
    if(loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

void SDLUtil::applySurface(int x, int y, SDL_Surface *source, SDL_Surface* destination) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
    return;
}

