#ifndef WORLD_H
#define WORLD_H

#include <iostream>
using namespace std;

#include "Location.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <chrono>
using namespace std;
using namespace sf;

enum CollideMask { AIR, WALL, HOUSE1, HOUSE2, HOUSE3, POISON, HEAL, SPEED, PV, ARROW };

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
            void initMap();
            void drawMap(RenderTarget&);
            int collideWith(RectangleShape&) const;

        protected:

        private:
            string worldName;
            Location* spawnLocation;
            Texture gameMapTexture;
            Sprite gameMap;
            int mask[24][40];
    };
}

#endif // WORLD_H
