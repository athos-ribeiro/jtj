#include "gameobject.h"

GameObject::~GameObject() {
    int size = children.size();
    for(int i = 0; i < size; i++) {
        if(children[i]) {
            delete children[i];
        }
    }
}

void GameObject::addChild(GameObject* child) {
    children.push_back(child);
}

void GameObject::draw(SDL_Surface *surface) {
    drawSelf(surface);
    int size = children.size();
    for(int i = size -1; i >= 0; i--) {
        if(children[i]) {
            children[i]->draw(surface);
        }
    }


}
