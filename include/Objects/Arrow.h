#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Potion.h"
#include "Frame.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace RPG
{
    class Arrow : public Potion
    {
        public:
            Arrow(string, int, float, Dir, Vector2f pos);
            virtual ~Arrow();
            string getName() const override;
            string toString() const override;
            IObject* clone() override;
            float getArrowPower() const;
            Dir getDirection() const;
            void remove();
            void tick(float, RenderTarget&);
            static void tickAll(float dt, RenderTarget& rt)
            {
                for(Arrow* a : Arrow::arrows)
                {
                    a->tick(dt, rt);
                }
            }

        protected:

        private:
            static vector<Arrow*> arrows;
            float arrowpower;
            Dir direction;
            Texture sheet;
            Sprite arrow;
    };
}

#endif // ARROW_H
