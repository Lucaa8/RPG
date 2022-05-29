#include "Game.h"

namespace RPG
{
    Game* Game::instance = nullptr; //must define instance here otherwise throws undefined reference.

    Game::Game() {}

    Game::~Game(){}

    void Game::init()
    {
        world = new World("world", new Location(0.0, 0.0, 0.0));
        window.create(VideoMode(1280, 720), "RPG");
        if (!defaultFont.loadFromFile("./arial.ttf")) //doesnt work when launched from c::b but works when exe is launched manually? wth?..another c::b bullshit ig
        {
            cout << "Failed to load default font file" << endl;
            return;
        }
    }

    void Game::loop()
    {
        //Initial time measurement
        auto tp = chrono::steady_clock::now();

        while (isGameRunning())
        {
            //Game events
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
            }

            //time measurement between each frames, so our hero isn't moving slower if timings between frames are big
            const auto new_tp = chrono::steady_clock::now();
            float deltaTime = chrono::duration<float>(new_tp-tp).count();
            tp = new_tp;

            //Read keyboad and set player direction
            Vector2f dir = {0.0f, 0.0f};
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                dir.y = -1.0f;
            }
            if(Keyboard::isKeyPressed(Keyboard::S))
            {
                dir.y = 1.0f;
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                dir.x = 1.0f;
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                dir.x = -1.0f;
            }
            if(Keyboard::isKeyPressed(Keyboard::F))
            {
                Frame* f = currentHero->getAnimation()->getCurrentFrame();
                if(f->getCurrent()!=AnimType::SHOOT)
                {
                    f->setCurrent(AnimType::SHOOT);
                }
                Bow* b = dynamic_cast<Bow*>(currentHero->getObject());
                if(b!=nullptr)
                {
                    if(b->isBent())
                    {
                        f->run = false;
                    }
                    else
                    {
                        b->tick(deltaTime);
                    }
                }
            }
            else
            {
                Bow* b = dynamic_cast<Bow*>(currentHero->getObject());
                if(b!=nullptr)
                {
                    if(b->isInUse())
                    {
                        b->shoot();
                        currentHero->getAnimation()->getCurrentFrame()->setCurrent(AnimType::WALKING);
                    }
                }
            }
            //Erase all the window
            window.clear();

            //Update our current hero position, motion, etc..
            currentHero->setDirection(dir); //maybe make one method which set dir and update all in one?
            currentHero->update(deltaTime);
            currentHero->draw(window, defaultFont);

            //Re-draw all
            window.display();
        }
    }

    bool Game::isGameRunning() const
    {
        return window.isOpen();
    }

    bool Game::addHero(Hero* hero)
    {
        if(getHero(hero->getName())==nullptr)
        {
            entities.push_back(hero);
            cout << hero->getName() << " joined the game!" << endl;
            if(entities.size()==1) //if its the only hero currently in the game, you control it.
            {
                setCurrentHero(hero);
            }
            return true;
        }
        return false;
    }

    bool Game::removeHero(string name)
    {
        Hero* h = getHero(name);
        if(h!=nullptr)
        {
            if(h==currentHero)
            {
                cout << "You can't remove the hero you're playing with now." << endl;
                return false;
            }
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
        return nullptr;
    }

    void Game::setCurrentHero(Hero* hero)
    {
        if(getHero(hero->getName())!=nullptr)
        {
            currentHero = hero;
            cout << "You are now playing with " << hero->getName() << endl;
        }
        else
        {
            cout << "You can't play with " << hero->getName() << " because she/he isn't in your team!" << endl;
        }
    }

    Hero* Game::getCurrentHero() const
    {
        return currentHero;
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
