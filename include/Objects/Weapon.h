#ifndef WEAPON_H
#define WEAPON_H

#include "IObject.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace RPG
{
    class Weapon : public IObject
    {
        public:
            Weapon();
            Weapon(string, double, double);
            virtual ~Weapon();
            string getName() const override;
            int getFeature() const override;
            string toString() const override;
            double getDamage() const;
            double getRange() const;
            string getWeaponName() const;
            IObject* clone() override;

        protected:

        private:
            string weaponName;
            double weaponDamage;
            double weaponRange;

    };
}

#endif // WEAPON_H
