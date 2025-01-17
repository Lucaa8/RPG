#include "Game.h"

namespace RPG
{
    Game* Game::instance = nullptr; //must define instance here otherwise throws undefined reference.

    Game::Game() {}

    Game::~Game(){}

    void Game::writeCenter(string txt, int fontSize, int y)
    {
        Text label(txt, defaultFont, fontSize);
        float w = label.getGlobalBounds().width;
        float h = label.getGlobalBounds().height;
        label.setPosition(window.getSize().x/2-w/2, y==-1?(window.getSize().y/2-h/2):y);
        window.draw(label);
    }

    void Game::init()
    {
        log("Started game!");
        world = new World("world", new Location(0.0, 0.0, 0.0));
        window.create(VideoMode(1280, 768), "RPG");
        if (!defaultFont.loadFromFile("./arial.ttf")) //doesnt work when launched from c::b but works when exe is launched manually? wth?..another c::b bullshit ig
        {
            print("Failed to load default font file", true);
            return;
        }
    }

    void Game::loop()
    {
        //Initial time measurement
        auto tp = chrono::steady_clock::now();

        bool escToggle = false;
        bool tabToggle = false;

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
            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                if(!escToggle)
                {
                    escToggle = true;
                    isPaused=!isPaused;
                    if(isPaused)
                    {
                        window.clear(Color(128, 128, 128, 255));
                        writeCenter("Game paused", 50, -1);
                        window.display();
                    }
                }
            }
            else
            {
                escToggle = false;
            }

            if(isPaused)
                continue;

            tabToggle = Keyboard::isKeyPressed(Keyboard::Tab);

            currentHero->useWeapon(deltaTime, Mouse::isButtonPressed(Mouse::Left));

            //Erase all the window
            window.clear();

            //Draw the png map
            world->drawMap(window);

            //Tick all current created arrows
            Arrow::tickAll(deltaTime, window);

            //Update our current hero position, motion, etc..
            currentHero->setDirection(dir); //maybe make one method which set dir and update all in one?
            currentHero->update(world, deltaTime);
            currentHero->draw(window, defaultFont);

            //Draw the menu if the tab key is pressed (after everything so its not hidden by something
            if(tabToggle)
                drawMenu();

            //Re-draw all
            window.display();
        }
        if(currentHero->getHealth() <= 0)
        {
            Game::instance->print("You are dead.", true);
        }
        log("Ended game!");
    }

    void Game::drawMenu()
    {
        stringstream ss;
        ss << "Name: " << currentHero->getName();
        writeCenter(ss.str(), 40, 200);
        stringstream().swap(ss); //reset ss
        ss << "Health: " << currentHero->getHealth() << "HP";
        writeCenter(ss.str(), 40, 270);
        stringstream().swap(ss); //reset ss
        ss << "Speed: " << currentHero->getAgility() << "PX";
        writeCenter(ss.str(), 40, 340);
        stringstream().swap(ss); //reset ss
        Location* l = currentHero->getLocation();
        ss << "X: " << static_cast<int>(l->getX()) << " Y: " << static_cast<int>(l->getY());
        writeCenter(ss.str(), 40, 410);
        Bow* b = dynamic_cast<Bow*>(currentHero->getObject());
        if(b!=nullptr)
        {
            stringstream().swap(ss); //reset ss
            ss << "Arrow left: " << b->getArrows();
            writeCenter(ss.str(), 40, 480);
        }
    }

    string getTime()
    {
        time_t t = std::time(nullptr);
        tm* now = std::localtime(&t);
        char buffer[128];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %X", now);
        return buffer;
    }

    void Game::log(string log)
    {
        fstream file(pathLog, ios::out | ios::app);
        if (file.is_open())
        {
            file << getTime() << ": " << log << endl;
            file.close();
        }
    }

    void Game::print(string str, bool outEndl)
    {
        cout << str;
        if(outEndl)
            cout << endl;
        log(str);
    }

    bool Game::isGameRunning() const
    {
        return window.isOpen();
    }

    void Game::stop()
    {
        window.close();
    }

    bool Game::addHero(Hero* hero)
    {
        if(getHero(hero->getName())==nullptr)
        {
            entities.push_back(hero);
            print(static_cast<ostringstream*>(&(ostringstream() << hero->getName() << " joined the game!"))->str(), true);
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
                print("You can't remove the hero you're playing with now.", true);
                return false;
            }
            entities.erase(entities.begin()+getIndex<Hero*>(entities, h));
            print(static_cast<ostringstream*>(&(ostringstream() << h->getName() << " left the game!"))->str(), true);
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
            print(static_cast<ostringstream*>(&(ostringstream() << "You are now playing with " << hero->getName()))->str(), true);
        }
        else
        {
            print(static_cast<ostringstream*>(&(ostringstream() << "You can't play with " << hero->getName() << " because she/he isn't in your team!"))->str(), true);
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
