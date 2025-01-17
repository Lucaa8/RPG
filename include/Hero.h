#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#include "IObject.h"
#include "Bow.h"
#include "Arrow.h"
#include "Potion.h"
#include "Shield.h"
#include "Location.h"
#include "Backpack.h"
#include "Animation.h"
#include "World.h"

namespace RPG
{
    class Hero
    {
        public:
            Backpack backpack = Backpack();
            static double const interactDistance; //max distance between 2 hero to allow interactions
            Hero();
            Hero(const Hero&);
            Hero(int, int, int, double, string, IObject*, Location*, Animation*);
            virtual ~Hero();
            virtual bool interact(const Hero&) const = 0;
            bool damage(const Hero&);
            void teleport(double, double, double);
            void teleport(const Location&);
            void teleport(const Hero&);
            friend ostream& operator<<(ostream&, const Hero&);

            //GETTERS
            string getName() const;
            int getQuest() const;
            int getStrength() const;
            int getAgility() const;
            int getIQ() const;
            double getHealth() const;
            IObject* getObject() const;
            void setLocation(double x, double y);
            Location* getLocation() const;

            //Graphical part
            sf::Sprite& getSprite();
            sf::RectangleShape& getHitbox();
            Animation* getAnimation() const;
            void draw(sf::RenderTarget&, sf::Font&) const;
            void setDirection(const sf::Vector2f& dir);
            void useWeapon(float, bool);
            void update(World*, float);

        protected:
            void setObject(IObject* newObject);
            virtual void show() const = 0;

        private:
            int strength;
            int agility;
            int intelligence;
            double hp;
            string name;
            int quest;
            IObject* object;
            Location* loc; //still using this class to store the sprite's pos instead of vect2f but not using z coord. Because teleport methods are useful
            sf::Vector2f velocity = {0.0f, 0.0f};
            sf::Sprite sprite;
            sf::RectangleShape hitbox;
            Animation* frames;

            //bricolage
            bool talkToGerrin = false;
            bool didBuy = false;

            //SETTERS
            void setHealth(double);
    };
}

#endif // HERO_H
