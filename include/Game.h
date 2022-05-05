#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <chrono>
using namespace std;
using namespace sf;

#include "World.h"
#include "Hero.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Necromancer.h"
#include "Animation.h"
//#include "Location.h" //already included in World.h or Hero.h

namespace RPG
{
    class Game
    {
        public:
            Game();
            ~Game();
            static Game* instance;
            void init();
            void loop();
            void paint();
            bool isGameRunning() const;
            Hero* getHero(string);
            void setCurrentHero(Hero* hero);
            Hero* getCurrentHero() const;
            World* getWorld();
            bool addHero(Hero*);
            bool removeHero(string);
            vector<Hero*> getHeroes() const;

        protected:

        private:
            RenderWindow window;
            Font defaultFont;
            bool isPaused = false;
            World* world;
            Hero* currentHero;
            vector<Hero*> entities;
            template <typename T>
            int getIndex(vector<T> vec, T toFind);
    };
}

#endif // GAME_H
