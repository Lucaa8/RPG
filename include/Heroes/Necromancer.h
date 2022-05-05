#ifndef NECROMANCER_H
#define NECROMANCER_H

#include "Wizard.h"

namespace RPG
{
    class Necromancer : public Wizard
    {
        public:
            Necromancer();
            Necromancer(int, int, int, double, string, Potion*, Location*, Animation*, int);
            ~Necromancer();
            void riseUndeads();

        protected:

        private:
    };
}

#endif // NECROMANCER_H
