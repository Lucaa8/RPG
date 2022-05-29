#include "Bow.h"

namespace RPG
{
    double const Bow::maxDrawingTime = 1.30f;

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

    bool Bow::shoot()
    {
        bool shot = false;
        if(arrows>0 && currentDrawingTime>0.4f) //little delay so player can't spam close arrows
        {
            double power = (currentDrawingTime/maxDrawingTime)*getRange();
            arrows--;
            cout << "shot at distance " << power << ". Remaining arrows " << arrows << endl;
            shot = true;
        }
        currentDrawingTime = 0;
        return shot;
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
        stringstream ss;
        ss << "Bow implements Weapon implements IObject{Name=" << getWeaponName() << ", Damage=" << getDamage() << ", Reach=" << getRange() << ", Arrows=" << getArrows() << ", DrawingTime=" << currentDrawingTime << "}";
        return ss.str();
    }

    IObject* Bow::clone()
    {
        return new Bow(getArrows(), currentDrawingTime);
    }
}
