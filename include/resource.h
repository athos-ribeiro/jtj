#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

using namespace std;

class Resource {
    public:
        virtual void load(const string& name) = 0;
};
#endif
