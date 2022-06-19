#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
using namespace std;
using namespace sf;

#include "Arrow.h"
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
            void stop();
            bool isGameRunning() const;
            void drawMenu();
            Hero* getHero(string);
            void setCurrentHero(Hero* hero);
            Hero* getCurrentHero() const;
            World* getWorld();
            bool addHero(Hero*);
            bool removeHero(string);
            void log(string);
            void print(string, bool);
            vector<Hero*> getHeroes() const;

        protected:

        private:
            void writeCenter(string, int, int);
            RenderWindow window;
            Font defaultFont;
            bool isPaused = false;
            string pathLog = "logs.txt";
            World* world;
            Hero* currentHero;
            vector<Hero*> entities;
            template <typename T>
            int getIndex(vector<T> vec, T toFind);
    };
}

#endif // GAME_H
