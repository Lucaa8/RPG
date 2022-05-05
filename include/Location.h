#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

namespace RPG
{
    class Location
    {
        public:
            Location();
            Location(double, double, double);
            ~Location();
            double getX() const;
            double getY() const;
            double getZ() const;
            void setX(double);
            void setY(double);
            void setZ(double);
            void add(double, double, double);
            friend ostream& operator<<(ostream&, const Location&);
            static double getDistance(const Location&, const Location&);
            Location* clone();

        protected:

        private:
            double x;
            double y;
            double z;
    };
}

#endif // LOCATION_H
