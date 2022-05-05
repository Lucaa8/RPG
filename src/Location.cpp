#include "Location.h"

namespace RPG
{
    Location::Location() : x(0), y(0), z(0) {}

    Location::Location(double x, double y, double z) : x(x), y(y), z(z) {}

    Location::~Location()
    {
        //dtor
    }

    double Location::getX() const
    {
        return x;
    }

    double Location::getY() const
    {
        return y;
    }

    double Location::getZ() const
    {
        return z;
    }

    void Location::setX(double x)
    {
        this->x = x;
    }

    void Location::setY(double y)
    {
        this->y = y;
    }

    void Location::setZ(double z)
    {
        this->z = z;
    }

    void Location::add(double x, double y, double z)
    {
        setX(getX()+x);
        setY(getY()+y);
        setZ(getZ()+z);
    }

    ostream& operator<<(ostream &s, const Location &h)
    {
        cout << setprecision(2) << fixed << "Location{x=" << h.getX() << ", y=" << h.getY() << ", z=" << h.getZ() << "}";
        return s;
    }

    double Location::getDistance(const Location& loc1, const Location& loc2)
    {
        return sqrt(pow(loc2.getX() - loc1.getX(), 2) + pow(loc2.getY() - loc1.getY(), 2) + pow(loc2.getZ() - loc1.getZ(), 2) * 1.0);
    }

    Location* Location::clone()
    {
        return new Location(getX(), getY(), getZ());
    }
}

