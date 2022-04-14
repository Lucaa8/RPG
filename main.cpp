#include <iostream>
#include <unistd.h>

#include "Game.h"

using namespace std;
using namespace RPG;

Game g;

int main()
{
    g.init();
    //strength, agility, intelligence, hp, name, object*, loc*
    g.addHero(new Warrior(100, 20, 30, 100.0, "Dokkaebi", new Weapon("MK 14 EBR", 60.0, 100.0), new Location(103.5, 61.0, -100.5)));
    g.addHero(new Wizard(20, 5, 90, 100.0, "Valkyrie", new Potion("Damage", 5), new Location(100.5, 60.0, -100.5), 10));
    g.addHero(new Warrior(80, 25, 20, 100.0, "Jager", new Shield(5), new Location(105, 61.0, -140.0)));
    g.addHero(new Necromancer(10, 13, 110, 100.0, "Doc", new Potion("Health", 3), new Location(110.7, 62.0, -105.5), 15));

    Weapon* w1 = new Weapon("W1", 1.0, 4.0);
    Weapon* w2 = new Weapon("W2", 2.0, 5.0);
    Weapon* w3 = new Weapon("W3", 3.0, 6.0);
    Shield* s1 = new Shield(10);
    Shield* s2 = new Shield(20);
    Potion* p1 = new Potion("P1", 1);
    Potion* p2 = new Potion("P2", 2);

    Hero* h = g.getHero("Dokkaebi");
    h->backpack.pack(w1);
    h->backpack.pack(w2);
    h->backpack.pack(w3);
    h->backpack.pack(s1);
    h->backpack.pack(s2);
    h->backpack.pack(p1);
    h->backpack.pack(p2);

    while(!h->backpack.isEmpty())
    {
        IObject* o = h->backpack.unpack();
        cout << o->toString() << endl;
        delete o;
    }

    cout << endl << "=== My team ===" << endl;
    for(auto* h : g.getHeroes())
    {
        cout << h->getName() << endl;
    }
    cout << "=== My team ===" << endl;

    cout << endl << "Current commands;" << endl <<
    "i1    : Interaction between Dokkaebi and Valkyrie" << endl <<
    "i2    : Interaction between Valkyrie and Dokkaebi" << endl <<
    "d1    : Valkyrie damage Dokkaebi" << endl <<
    "d2    : Dokkaebi damage Valkyrie" << endl <<
    "c     : Valkyrie cast spell" << endl <<
    "s1    : Show Dokkaebi" << endl <<
    "s2    : Show Valkyrie" << endl <<
    "tp    : Teleport Dokkaebi to Valkyrie" << endl <<
    "spawn : Teleport Dokkaebi to spawn" << endl <<
    "stop  : Stop the game" << endl;

    while(g.isGameRunning())
    {
        g.loop();
        usleep(50000); //20 ticks (not useful rn because of the cin in loop() but nvm)
    }

    return 0;
}
