#include "Bow.h"

namespace RPG
{
    double const Bow::maxDrawingTime = 0.9f;

    Bow::Bow(int arrows, int currentDrawingTime) : Weapon("Bow", 45, 50), arrows(arrows), currentDrawingTime(currentDrawingTime) {}

    Bow::Bow(int arrows) : Weapon("Bow", 45, 50), arrows(arrows), currentDrawingTime(0) {}

    Bow::Bow() : Weapon("Bow", 45, 50), arrows(10), currentDrawingTime(0) {}

    Bow::~Bow()
    {
        //dtor
    }

    int Bow::getArrows() const
    {
        return arrows;
    }

    void Bow::tick(float dt)
    {
        currentDrawingTime+=dt;
        if(currentDrawingTime>maxDrawingTime)
        {
            currentDrawingTime = maxDrawingTime;
        }
    }

    double Bow::shoot()
    {
        double power = -1.f;
        if(arrows>0 && currentDrawingTime>0.3f) //little delay so player can't spam close arrows
        {
            power = (currentDrawingTime/maxDrawingTime)*getRange();
            arrows--;
        }
        currentDrawingTime = 0;
        return power;
    }

    bool Bow::isInUse() const
    {
        return currentDrawingTime > 0;
    }

    bool Bow::isBent() const
    {
        return currentDrawingTime >= maxDrawingTime;
    }

    string Bow::toString() const
    {
        std::stringstream ss;
        ss << "Bow implements Weapon implements IObject{Name=" << getWeaponName() << ", Damage=" << getDamage() << ", Reach=" << getRange() << ", Arrows=" << getArrows() << ", DrawingTime=" << currentDrawingTime << "}";
        return ss.str();
    }

    IObject* Bow::clone()
    {
        return new Bow(getArrows(), currentDrawingTime);
    }
}
