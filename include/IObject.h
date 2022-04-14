#ifndef IOBJECT_H
#define IOBJECT_H

#include <iostream>
using namespace std;

namespace RPG
{
    class IObject
    {
        public:
            virtual ~IObject(){}
            virtual string getName() const = 0;
            virtual int getFeature() const = 0;
            virtual string toString() const = 0;
            virtual IObject* clone() = 0;
    };
}

#endif // IOBJECT_H
