#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

typedef struct SDL_Surface SDL_Surface;

using namespace std;

class GameObject {

    vector<GameObject*> children;
    virtual void drawSelf(SDL_Surface *surface) = 0;
    public:
        virtual ~GameObject();
        void draw(SDL_Surface *surface);
        void addChild(GameObject* child);
};


#endif
