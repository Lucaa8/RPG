#ifndef FRAME_H
#define FRAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

class Frame
{
    //standard: 64x64
    //attack:   256x192
    public:
        Frame();
        Frame(string, string, int, int, int, int);
        Frame(const Frame&);
        ~Frame();
        void apply(Sprite&);
        void next();
        string getUid() const;
        void setFrameX(int);
        void setFrameY(int);
        bool run;

    private:
        string uid;
        Texture texture;
        int maxFrames;
        int current;
        IntRect** frames;
};

#endif // FRAME_H
