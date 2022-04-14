#include "Game.h"

namespace RPG
{
    Game::Game() {}

    Game::~Game(){}

    void Game::init()
    {
        world = new World("world", new Location(0.0, 0.0, 0.0));
        isRunning = true;
    }

    void Game::loop()
    {
        //Test programm for now
        string cmd = "";
        cin >> cmd;
        Hero* h1 = entities.at(0);
        Hero* h2 = entities.at(1);
        if(cmd=="i1")
        {
            h1->interact(*h2);
        }
        else if(cmd=="i2")
        {
            h2->interact(*h1);
        }
        else if(cmd=="d1")
        {
            h1->damage(*h2);
        }
        else if(cmd=="d2")
        {
            h2->damage(*h1);
        }
        else if(cmd=="c")
        {
            Wizard* w = (Wizard*)h2;
            w->castSpeel();
        }
        else if(cmd=="s1")
        {
            cout << *h1 << endl;
        }
        else if(cmd=="s2")
        {
            cout << *h2 << endl;
        }
        else if(cmd=="tp")
        {
            h1->teleport(*h2);
        }
        else if(cmd=="spawn")
        {
            h1->teleport(world->getSpawnLocation());
        }
        else if(cmd=="stop")
        {
            isRunning = false;
        }
        //read keys, call events, etc..
    }

    bool Game::isGameRunning() const
    {
        return isRunning;
    }

    bool Game::addHero(Hero* hero)
    {
        if(getHero(hero->getName())==NULL)
        {
            entities.push_back(hero);
            cout << hero->getName() << " joined the game!" << endl;
            return true;
        }
        return false;
    }

    bool Game::removeHero(string name)
    {
        Hero* h = getHero(name);
        if(h!=NULL)
        {
            entities.erase(entities.begin()+getIndex<Hero*>(entities, h));
            cout << h->getName() << " left the game!" << endl;
            delete h;
            return true;
        }
        return false;
    }

    Hero* Game::getHero(string name)
    {
        for(Hero* h : entities)
        {
            if(h->getName()==name)
                return h;
        }
        return NULL;
    }

    vector<Hero*> Game::getHeroes() const
    {
        return entities;
    }

    World* Game::getWorld()
    {
        return world;
    }

    //Useful if we have multiples vector to get index from
    template <typename T>
    int Game::getIndex(vector<T> vec, T toFind) {
        int index = -1;
        auto it = find(vec.begin(), vec.end(), toFind);
        if (it != vec.end())
        {
            index = it - vec.begin();
        }
        return index;
    }
}
