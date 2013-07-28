#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <SDL/SDL.h>
#include <string>

class SDLUtil {
    public:
    static SDL_Surface *loadImage(std::string filename);
    static void applySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* clip = NULL);
};

#endif
