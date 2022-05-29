#include "Weapon.h"

namespace RPG
{
    Weapon::Weapon() :
        weaponName("defaultWeapon"),
        weaponDamage(0.0),
        weaponRange(0.0) {}

    Weapon::Weapon(string weaponName, double weaponDamage, double weaponRange) :
        weaponName(weaponName),
        weaponDamage(weaponDamage),
        weaponRange(weaponRange) {}

    Weapon::~Weapon() {}

    string Weapon::getName() const
    {
        return "Weapon";
    }

    int Weapon::getFeature() const
    {
        return weaponDamage;
    }

    string Weapon::getWeaponName() const
    {
        return weaponName;
    }

    double Weapon::getDamage() const
    {
        return weaponDamage;
    }

    double Weapon::getRange() const
    {
        return weaponRange;
    }

    string Weapon::toString() const
    {
        stringstream ss;
        ss << "Weapon implements IObject{Name=" << getWeaponName() << ", Damage=" << getDamage() << ", Reach=" << getRange() << "}";
        return ss.str();
    }

    IObject* Weapon::clone()
    {
        return new Weapon(getName(), getDamage(), getRange());
    }
}
