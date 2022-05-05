#ifndef WARRIOR_H
#define WARRIOR_H

#include "Hero.h"
#include "Weapon.h" //for the default weapon
#include "Animation.h"

#include <iostream>
using namespace std;

namespace RPG
{
    class Warrior : public Hero
    {
        public:
            Warrior();
            Warrior(int, int, int, double, string, IObject*, Location*, Animation*);
            virtual ~Warrior();
            bool interact(const Hero&) const override;
            void show() const override;

        protected:

        private:
    };
}

#endif // WARRIOR_H
