#ifndef BOW_H
#define BOW_H

#include "Weapon.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace RPG
{
    class Bow : public Weapon
    {
        public:
            Bow(int, int);
            Bow(int);
            Bow();
            static double const maxDrawingTime; //time needed to draw the bow (must be the animation's frameTime*nb of frames for shoot
            virtual ~Bow();
            int getArrows() const;
            string toString() const override;
            IObject* clone() override;
            void tick(float);
            double shoot();
            bool isInUse() const override;
            bool isBent() const;

        protected:

        private:
            int arrows;
            double currentDrawingTime;
    };
}

#endif // BOW_H
