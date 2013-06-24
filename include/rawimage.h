#ifndef RAWIMAGE_H
#define RAWIMAGE_H

#include "resource.h"
#include <SDL/SDL.h>

using namespace std;

class RawImage : public Resource {
    SDL_Surface *_pixels;
    public:
        RawImage();
        ~RawImage();
        void load(const string& name);
        int width() const;
        int height() const;
        SDL_Surface *pixels() const;
};
#endif
