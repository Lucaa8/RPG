#include "Wizard.h"

namespace RPG
{
    Wizard::Wizard(int strength, int agility, int intelligence, double hp, string name, Potion* potion, Location* loc, int mana) :
        Hero(strength, agility, intelligence, hp, name, potion, loc), mana(mana) {}

    Wizard::Wizard() : Hero(), mana(0)
    {
        setObject(new Potion("defaultEffect", 1));
    }

    Wizard::~Wizard() {}

    void Wizard::castSpeel()
    {
        if(getMana()>=2)
        {
            cout << getName() << ": " << "Fireball!" << endl;
            mana-=2;
        }
        else
        {
            cout << getName() << ": Pas assez de mana!" << endl;
        }
    }

    int Wizard::getMana() const
    {
        return mana;
    }

    bool Wizard::interact(const Hero& hero) const
    {
        bool canInteract = Hero::interact(hero); //call superclass method (of instance)
        if(canInteract)
        {
            cout << "===Wizard interaction===" << endl;
            cout << getName() << " > Hello " << hero.getName() << " how are you?!" << endl;
            cout << "===Wizard interaction===" << endl;
        }
        return canInteract;
    }

    void Wizard::show() const
    {
        cout <<
        "==================" << endl <<
        "HERO: " << getName() << endl <<
        "Type: Wizard" << endl <<
        "==================" << endl <<
        "mana:" << mana << endl <<
        "strength: " << getStrength() << endl <<
        "agility: " << getAgility() << endl <<
        "intelligence: " << getIQ() << endl <<
        "HP: " << getHealth() << endl <<
        getObject()->toString() << endl <<
        "location: " << *(getLocation()) << endl <<
        "==================" << endl;
    }
}
