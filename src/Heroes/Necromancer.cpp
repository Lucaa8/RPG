#include "Necromancer.h"

namespace RPG
{
    Necromancer::Necromancer(int strength, int agility, int intelligence, double hp, string name, Potion* potion, Location* loc, int mana) :
        Wizard(strength, agility, intelligence, hp, name, potion, loc, mana) {}

    Necromancer::Necromancer() : Wizard() {}

    Necromancer::~Necromancer()
    {
        //dtor
    }

    void Necromancer::riseUndeads()
    {
        if(getMana()>=3)
        {
            cout << getName() << ": Rise undeads!" << endl;
            mana-=3;
        }
        else
        {
            cout << getName() << ": Pas assez de mana!" << endl;
        }
    }
}

