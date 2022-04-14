#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "World.h"
#include "Hero.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Necromancer.h"
//#include "Location.h" //already included in World.h or Hero.h

namespace RPG
{
    class Game
    {
        public:
            Game();
            ~Game();
            void init();
            void loop();
            bool isGameRunning() const;
            Hero* getHero(string);
            World* getWorld();
            bool addHero(Hero*);
            bool removeHero(string);
            vector<Hero*> getHeroes() const;

        protected:

        private:
            bool isRunning = false;
            World* world;
            vector<Hero*> entities;
            template <typename T>
            int getIndex(vector<T> vec, T toFind);
    };
}

#endif // GAME_H
