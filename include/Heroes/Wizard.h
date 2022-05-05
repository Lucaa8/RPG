#ifndef WIZARD_H
#define WIZARD_H

#include "Hero.h"
#include "Potion.h"
#include "Animation.h"

#include <iostream>
using namespace std;

namespace RPG
{
    class Wizard : public Hero
    {
        public:
            Wizard();
            Wizard(int, int, int, double, string, Potion*, Location*, Animation*, int);
            virtual ~Wizard();
            void castSpeel();
            bool interact(const Hero&) const override;
            int getMana() const;
            void show() const override;

        protected:
            int mana = 0;

        private:
    };
}

#endif // WIZARD_H
