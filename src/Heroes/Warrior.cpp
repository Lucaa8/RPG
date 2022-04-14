#include "Warrior.h"

namespace RPG
{
    Warrior::Warrior() : Hero()
    {
        setObject(new Weapon());
    }

    Warrior::Warrior(int strength, int agility, int intelligence, double hp, string name, IObject* object, Location* loc) :
        Hero(strength, agility, intelligence, hp, name, object, loc) {}

    Warrior::~Warrior()
    {
        //dtor
    }

    void Warrior::show() const
    {
        cout <<
        "==================" << endl <<
        "HERO: " << getName() << endl <<
        "Type: Warrior" << endl <<
        "==================" << endl <<
        "strength: " << getStrength() << endl <<
        "agility: " << getAgility() << endl <<
        "intelligence: " << getIQ() << endl <<
        "HP: " << getHealth() << endl <<
        getObject()->toString() << endl <<
        "location: " << *(getLocation()) << endl <<
        "==================" << endl;
    }

    bool Warrior::interact(const Hero& hero) const
    {
        bool canInteract = Hero::interact(hero); //call superclass method (of instance)
        if(canInteract)
        {
            cout << "===Warrior interaction===" << endl;
            cout << getName() << " > Hello " << hero.getName() << " how are you?!" << endl;
            cout << "===Warrior interaction===" << endl;
        }
        return canInteract;
    }
}

