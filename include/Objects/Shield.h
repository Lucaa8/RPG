#ifndef SHIELD_H
#define SHIELD_H

#include "IObject.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace RPG
{
    class Shield : public IObject
    {
        public:
            Shield(int);
            virtual ~Shield();
            string getName() const override;
            int getFeature() const override;
            string toString() const override;
            IObject* clone() override;

        protected:

        private:
            int solidity = 0;
    };
}

#endif // SHIELD_H
