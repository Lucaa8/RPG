#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Location.h"

namespace RPG
{
    class World
    {
        public:
            World(string, Location* spawnLoc);
            ~World();
            string getWorldName() const;
            void setSpawnLocation(Location* loc);
            void setSpawnLocation(double, double, double);
            Location* getSpawnLocation() const;

        protected:

        private:
            string worldName;
            Location* spawnLocation;
    };
}

#endif // WORLD_H
