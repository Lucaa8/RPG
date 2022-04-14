#include "Hero.h"

namespace RPG
{
    double const Hero::interactDistance = 7.0;

    Hero::Hero() :
        strength(0),
        agility(0),
        intelligence(0),
        hp(0),
        name("no_name"),
        object(nullptr),
        loc(new Location()) {}

    Hero::Hero(int strength, int agility, int intelligence, double hp, string name, IObject* object, Location* loc) :
        strength(strength),
        agility(agility),
        intelligence(intelligence),
        hp(hp),
        name(name),
        object(object),
        loc(loc) {}

    Hero::Hero(const Hero& hero) :
        strength(hero.strength),
        agility(hero.agility),
        intelligence(hero.intelligence),
        hp(hero.hp),
        name(hero.name),
        object(hero.getObject()->clone()),
        loc(hero.getLocation()->clone()) {}

    Hero::~Hero()
    {
        delete object;
        delete loc;
    }

    ostream& operator<<(ostream &s, const Hero &h)
    {
        h.show();
        return s;
    }

    bool Hero::interact(const Hero& hero) const
    {
        if(getHealth()>0)
        {
            if(Location::getDistance(*(this->loc), *(hero.getLocation())) <= interactDistance)
            {
                return true;
            }else
            {
                cout << "These two heroes are too far away from each oder. Interaction isn't allowed." << endl;
            }
        }
        else
        {
            cout << "Cannot interact with a dead hero, what are you doing??" << endl;
        }
        return false;
    }

    //maybe in Weapon.cpp ?
    bool Hero::damage(const Hero& hero)
    {
        Weapon* w = dynamic_cast<Weapon*>(object);
        if(w!=nullptr)
        {
            //check if the damager his in range to attack the victim
            if(Location::getDistance(*(this->loc), *(hero.getLocation())) <= w->getRange())
            {
                //maybe check if target does have a shield, if yes, cancel attack but remove 1 solidity? if no hit successful ?
                setHealth(getHealth()-w->getDamage());
                if(getHealth()<=0)
                {
                    //death
                    cout << name << " is now dead. Killed by " << hero.getName() << " with " << w->getWeaponName() << "!" << endl;
                    setHealth(0);
                }
                else
                {
                    cout << name << " took " << w->getDamage() << " damage. HP left: " << getHealth() << endl;
                }
                return true;
            }
            else
            {
                cout << "Target to far away from you. Cannot hit." << endl;
            }
        }
        else
        {
            cout << "Cannot attack another hero without a weapon" << endl;
        }
        return false;
    }

    void Hero::teleport(double x, double y, double z)
    {
        cout << this->name << " was teleported from " << *loc;
        loc->setX(x);
        loc->setY(y);
        loc->setZ(z);
        cout << " to " << *loc << endl;
    }

    void Hero::teleport(const Location* loc)
    {
        this->teleport(loc->getX(), loc->getY(), loc->getZ());
    }

    void Hero::teleport(const Hero& hero)
    {
        this->teleport(hero.getLocation());
    }

    void Hero::setObject(IObject* newObject)
    {
        this->object = newObject;
    }

    void Hero::setHealth(double health)
    {
        this->hp = health;
    }

    string Hero::getName() const
    {
        return name;
    }

    int Hero::getStrength() const
    {
        return strength;
    }

    int Hero::getAgility() const
    {
        return agility;
    }

    int Hero::getIQ() const
    {
        return intelligence;
    }

    double Hero::getHealth() const
    {
        return hp;
    }

    IObject* Hero::getObject() const
    {
        return object;
    }

    Location* Hero::getLocation() const
    {
        return loc;
    }
}

