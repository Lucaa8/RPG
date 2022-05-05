#include <iostream>
#include <unistd.h>

#include "Game.h"

using namespace std;
using namespace RPG;

Game g;

int main()
{
    Game::instance = &g;
    g.init();

    Animation* a = new Animation(0.1f);
    Frame** f = new Frame*[6];
    f[0] = new Frame("w0_s0_0", "sprites/artena/noweapon_unstuffed.png", 9, 10, 64, 64);
    f[1] = new Frame("w0_s1_0", "sprites/artena/noweapon_stuffed_off.png", 9, 10, 64, 64);
    f[2] = new Frame("w0_s1_1", "sprites/artena/noweapon_stuffed_on.png", 9, 10, 64, 64);
    f[3] = new Frame("w1_s0_0", "sprites/artena/weapon_unstuffed.png", 9, 10, 64, 64);
    f[4] = new Frame("w1_s1_0", "sprites/artena/weapon_stuffed_off.png", 9, 10, 64, 64);
    f[5] = new Frame("w1_s1_1", "sprites/artena/weapon_stuffed_on.png", 9, 10, 64, 64);
    a->setFrames(f, 6);

    //strength, agility(speed), intelligence, hp, name, object*, loc*
    g.addHero(new Warrior(100, 150, 30, 100.0, "Arténa", new Weapon("Bow", 60.0, 100.0), new Location(0.0, 60.0, 0.0), a));
    g.addHero(new Warrior(100, 150, 30, 100.0, "Dokkaebi", new Weapon("MK 14 EBR", 60.0, 100.0), new Location(103.5, 61.0, -100.5), nullptr));
    g.addHero(new Wizard(20, 1, 90, 100.0, "Valkyrie", new Potion("Damage", 5), new Location(100.5, 60.0, -100.5), nullptr, 10));
    g.addHero(new Warrior(80, 3, 20, 100.0, "Jager", new Shield(5), new Location(105, 61.0, -140.0), nullptr));
    g.addHero(new Necromancer(10, 1, 110, 100.0, "Doc", new Potion("Health", 3), new Location(110.7, 62.0, -105.5), nullptr, 15));

    //g.addHero(new Archer(?, ?, ?, ?, "Arthéna", new Weapon("Bow", ?, ?), new Location(0, 0, 0), "ArthenaArcSansCasque.png"));

    g.loop();

    return 0;
}
