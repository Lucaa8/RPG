#include "Potion.h"

namespace RPG
{
    Potion::Potion(string effect, int power) : effect(effect), power(power){}

    Potion::~Potion() {}

    string Potion::getEffect() const
    {
        return effect;
    }

    string Potion::getName() const
    {
        return "Potion";
    }

    string Potion::toString() const
    {
        std::stringstream ss;
        ss << "Potion implements IObject{Effect=" << getEffect() << ", Power=" << getFeature() << "}";
        return ss.str();
    }

    int Potion::getFeature() const
    {
        return power;
    }

    IObject* Potion::clone()
    {
        return new Potion(getEffect(), getFeature());
    }
}
