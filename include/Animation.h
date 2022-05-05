#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#include "Frame.h"

class Animation
{
    public:
        Animation();
        Animation(float time);
        ~Animation();
        void setCurrentFrame(string);
        Frame* getCurrentFrame() const;
        void setFrames(Frame**, int);
        void tick(float, Sprite&);
        Animation* clone() const;

    private:
        float frameTime; //the time a single image of currFrame must be displayed
        float currTime; //the time the current image is displayed
        Frame* currFrame; //pointer on the current frame
        Frame** frames; //array of frames pointer (one frame by texture image, for example, one frame with sword and one without)
        int framesSize; //size of the array of frames
};

#endif // ANIMATION_H
