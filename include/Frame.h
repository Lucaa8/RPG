#ifndef FRAME_H
#define FRAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

enum AnimType { CASTSPELL=7405632, THRUST=276889664, WALKING=546373696, SLASH=811663424, SHOOT=1087438912, DEATH=1348534336, ATTACK=1415839936 };
enum Dir { BACK, LEFT, FRONT, RIGHT, NONE=-1 };

class Frame
{

    /*int cast =  encode(0, 7, 64, 64);
    int thrust =  encode(4, 8, 64, 64);
    int walking = encode(8, 9, 64, 64);
    int slash =   encode(12, 6, 64, 64);
    int shoot =   encode(16, 13, 64, 64);
    int death =   encode(20, 6, 64, 64);
    int attack =  encode(21, 6, 256, 192);

    cout << cast << endl << thrust << endl << walking << endl << slash << endl << shoot << endl << death << endl << attack << endl;*/

    //7405632
    //castspell back  : Y=0 Max=7 Size=64x64
    //castspell left  : Y=1 Max=7 Size=64x64
    //castspell front : Y=2 Max=7 Size=64x64
    //castspell right : Y=3 Max=7 Size=64x64

    //276889664
    //thrust back   : Y=4 Max=8 Size=64x64
    //thrust left   : Y=5 Max=8 Size=64x64
    //thrust front  : Y=6 Max=8 Size=64x64
    //thrust right  : Y=7 Max=8 Size=64x64

    //546373696
    //walking back   : Y=8  Max=9 Size=64x64
    //walking left   : Y=9  Max=9 Size=64x64
    //walking front  : Y=10 Max=9 Size=64x64
    //walking right  : Y=11 Max=9 Size=64x64

    //811663424
    //slash back  : Y=12 Max=6 Size=64x64
    //slash left  : Y=13 Max=6 Size=64x64
    //slash front : Y=14 Max=6 Size=64x64
    //slash right : Y=15 Max=6 Size=64x64

    //1087438912
    //shoot (bow) back  : Y=16 Max=13 Size=64x64
    //shoot (bow) left  : Y=17 Max=13 Size=64x64
    //shoot (bow) front : Y=18 Max=13 Size=64x64
    //shoot (bow) right : Y=19 Max=13 Size=64x64

    //1348534336
    //death : Y=20 Max=6 Size=64x64

    //1415839936
    //attack (sword) back  : Y=21 Max=6 Size=256x192 //à voir pour le y de départ sur l'image
    //attack (sword) left  : Y=22 Max=6 Size=256x192
    //attack (sword) front : Y=23 Max=6 Size=256x192
    //attack (sword) right : Y=24 Max=6 Size=256x192

    public:
        Frame();
        Frame(string, string);
        Frame(const Frame&);
        ~Frame();
        void apply(Sprite&);
        void next();
        string getUid() const;
        void setCurrent(AnimType);
        AnimType getCurrent() const;
        void setDirection(Dir);
        Dir getDirection() const;
        void setX(int);
        bool run;

    private:
        string uid;
        Texture texture;
        int maxFrames;
        int current;
        int currentAnimY;
        AnimType currentAnim;
        Dir currentDir;
        IntRect** frames;
        void updateFrames(int, int, int, int);
        void deleteFrames();
        void setY(int);
};

#endif // FRAME_H
