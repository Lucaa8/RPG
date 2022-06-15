#ifndef POTION_H
#define POTION_H

#include "IObject.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace RPG
{
    class Potion : public IObject
    {
        public:
            Potion(string, int);
            virtual ~Potion();
            string getEffect() const;
            string getName() const override;
            int getFeature() const override;
            string toString() const override;
            IObject* clone() override;

        protected: //because arrow extends Potion
            string effect;
            int power = 0;

        private:
    };
}

#endif // POTION_H
