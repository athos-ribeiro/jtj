#include "rawimage.h"
#include <SDL/SDL_image.h>

//TODO: THROW EXCEPTIONS ON LOAD METHOD

using namespace std;

RawImage::RawImage() {
    _pixels = NULL;
}

RawImage::~RawImage() {
    if(_pixels != NULL) {
        SDL_FreeSurface(_pixels);
    }
}

void RawImage::load(const string& name) {
    SDL_Surface *image = IMG_Load(name.c_str());

    if(image != NULL) {
        _pixels = SDL_DisplayFormatAlpha(image);
        SDL_FreeSurface(image);
    }
}
int RawImage::width() const {
    if(_pixels != NULL) {
        return _pixels->w;
    }
    else {
        return 0;
    }
}

int RawImage::height() const {
    if(_pixels != NULL) {
        return _pixels->h;
    }
    else {
        return 0;
    }
}
SDL_Surface* RawImage::pixels() const {
    return _pixels;
}
