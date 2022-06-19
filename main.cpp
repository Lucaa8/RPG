#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "Game.h"

using namespace std;
using namespace RPG;

Game g;

Hero* createArtena();
Hero* createGerrin();
Hero* createHadena();
Hero* createZora();

int askInput(int);
void showControls();

int main()
{

    Hero* artena = createArtena();
    Hero* gerrin = createGerrin();
    Hero* hadena = createHadena();
    Hero* zora   = createZora();

    int choice = -1;
    int nbHeroes = 1;

    cout << endl;
    showControls();
    cout << endl << "You can get more infos in game, you just need to walk in front of the PNJs and check your left upper corner." << endl << endl;

    do
    {
        cout << "Choose your Hero;" << endl <<
        "1)" << endl << *artena << endl << "Choix ? "; //only Aetena can fight rn...
        //"2)" << endl << *gerrin << endl << endl <<
        //"3)" << endl << *hadena << endl << endl <<
        //"4)" << endl << *zora << endl << "Choix ? ";
        try
        {
            choice = askInput(nbHeroes);
        }
        catch(const exception& e)
        {
            cout << "failed to read choice: " << e.what() << endl;
        }
    }while(choice==-1);

    Game::instance = &g;
    g.init();

    if(choice==1)
        g.addHero(artena);
    else if(choice==2)
        g.addHero(hadena);
    else if(choice==3)
        g.addHero(gerrin);
    else
        g.addHero( zora );

    g.addHero(gerrin);
    g.addHero(hadena);
    gerrin->teleport(Location(1218, 130, 0));
    hadena->teleport(Location(320, 418, 0));

    g.loop();

    system("pause");

    return 0;
}

Hero* createArtena()
{
    Animation* a = new Animation(0.1f);
    Frame** f = new Frame*[6];
    f[0] = new Frame("w0_s0_0", "sprites/artena/noweapon_unstuffed.png");
    f[1] = new Frame("w0_s1_0", "sprites/artena/noweapon_stuffed_off.png");
    f[2] = new Frame("w0_s1_1", "sprites/artena/noweapon_stuffed_on.png");
    f[3] = new Frame("w1_s0_0", "sprites/artena/weapon_unstuffed.png");
    f[4] = new Frame("w1_s1_0", "sprites/artena/weapon_stuffed_off.png");
    f[5] = new Frame("w1_s1_1", "sprites/artena/weapon_stuffed_on.png");
    a->setFrames(f, 6);
    a->setCurrentFrame("w1_s0_0");
                    //strength, agility(speed), intelligence, hp, name, object*, loc*
    return new Warrior(100, 150, 30, 100.0, "Arténa", new Bow(20), new Location(0.0, 60.0, 0.0), a);
}

Hero* createGerrin()
{
    Animation* a = new Animation(0.1f);
    Frame** f = new Frame*[1];
    f[0] = new Frame("w1_s0_0", "sprites/gerrin/weapon_unstuffed.png");
    a->setFrames(f, 1);
    return new Wizard(20, 100, 90, 100.0, "Gerrin", new Potion("Poison", 5), new Location(100.5, 60.0, -100.5), a, 10);
}

Hero* createHadena()
{
    Animation* a = new Animation(0.1f);
    Frame** f = new Frame*[2];
    f[0] = new Frame("w0_s0_0", "sprites/hadena/noweapon_unstuffed.png");
    f[1] = new Frame("w1_s0_0", "sprites/hadena/weapon_unstuffed.png");
    a->setFrames(f, 2);
    return new Wizard(10, 110, 110, 100.0, "Hadena", new Potion("Speed", 3), new Location(110.7, 62.0, -105.5), a, 10);
}

Hero* createZora()
{
    Animation* a = new Animation(0.1f);
    Frame** f = new Frame*[4];
    f[0] = new Frame("w0_s0_0", "sprites/zora/noweapon_unstuffed.png");
    f[1] = new Frame("w0_s1_0", "sprites/zora/noweapon_stuffed.png");
    f[2] = new Frame("w1_s0_0", "sprites/zora/weapon_unstuffed.png");
    f[3] = new Frame("w1_s1_0", "sprites/zora/weapon_stuffed.png");
    a->setFrames(f, 4);
    return new Warrior(100, 140, 30, 100.0, "Zora", new Shield(5), new Location(103.5, 61.0, -100.5), a);
}

int askInput(int maxChoice)
{
    int choice;
    int result = scanf("%d", &choice); //scanf because cin is bullshit
    if (result == EOF)
    {
        throw runtime_error("bad input");
    }
    if(result==0)
    {
        while (fgetc(stdin) != '\n'); //read buffer till reaching the \n (end of line)
        throw runtime_error("bad input");
    }
    if(choice<=0||choice>maxChoice)
    {
        throw runtime_error("bad choice");
    }
    return choice;
}

void showControls()
{
    cout << "You can control an hero in game by using;" << endl <<
    "WASD: Moving Up/Left/Down/Right" << endl <<
    "Mouse Left: Shoot with your bow. Longer pressed = more power" << endl <<
    "TAB: See your stats (shown while pressed)" << endl <<
    "ESC: Pause the game (toggle)" << endl;
}

