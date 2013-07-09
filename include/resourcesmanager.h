#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include "rawimage.h"
#include <vector>

class ResourcesManager {
    ResourcesManager();
    static ResourcesManager* instance = NULL;

    class ResourcesInfo {
        Resource* resource;
        int references;
        public:
            ResourcesInfo() {
                resource = NULL;
                references = 0;
            }
    };

    vector<ResourcesInfo*> resources;

    public:
        static ResourcesManager *getInstance();
        RawImage* getImage(const string &name);
        void release(RawImage* image);
        void load(const string &resourcesDescription);
};
#endif
