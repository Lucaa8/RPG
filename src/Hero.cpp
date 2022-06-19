#include "Hero.h"
#include "Game.h" //not good but no choice.. include loop otherwise (if including Game.h in header)

namespace RPG
{
    double const Hero::interactDistance = 7.0;

    //prototype
    RectangleShape drawHitbox(const IntRect&, const Sprite&);

    Hero::Hero() :
        strength(0),
        agility(0),
        intelligence(0),
        hp(0),
        name("no_name"),
        object(nullptr),
        loc(new Location()),
        frames(nullptr) {}

    Hero::Hero(int strength, int agility, int intelligence, double hp, string name, IObject* object, Location* loc, Animation* frames) :
        strength(strength),
        agility(agility),
        intelligence(intelligence),
        hp(hp),
        name(name),
        object(object),
        loc(loc),
        sprite(sf::Sprite()),
        frames(frames) {}

    Hero::Hero(const Hero& hero) :
        strength(hero.strength),
        agility(hero.agility),
        intelligence(hero.intelligence),
        hp(hero.hp),
        name(hero.name),
        object(hero.getObject()->clone()),
        loc(hero.getLocation()->clone()),
        frames(hero.frames->clone()) {}

    Hero::~Hero()
    {
        delete object;
        delete loc;
        delete frames;
    }


    ostream& operator<<(ostream &s, const Hero &h)
    {
        h.show();
        return s;
    }

    bool Hero::interact(const Hero& hero) const
    {
        if(getHealth()>0)
        {
            if(Location::getDistance(*(this->loc), *(hero.getLocation())) <= interactDistance)
            {
                return true;
            }else
            {
                cout << "These two heroes are too far away from each oder. Interaction isn't allowed." << endl;
            }
        }
        else
        {
            cout << "Cannot interact with a dead hero, what are you doing??" << endl;
        }
        return false;
    }

    //maybe in Weapon.cpp ?
    bool Hero::damage(const Hero& hero)
    {
        Weapon* w = dynamic_cast<Weapon*>(object);
        if(w!=nullptr)
        {
            //check if the damager his in range to attack the victim
            if(Location::getDistance(*(this->loc), *(hero.getLocation())) <= w->getRange())
            {
                //maybe check if target does have a shield, if yes, cancel attack but remove 1 solidity? if no hit successful ?
                setHealth(getHealth()-w->getDamage());
                if(getHealth()<=0)
                {
                    //death
                    cout << name << " is now dead. Killed by " << hero.getName() << " with " << w->getWeaponName() << "!" << endl;
                    setHealth(0);
                }
                else
                {
                    cout << name << " took " << w->getDamage() << " damage. HP left: " << getHealth() << endl;
                }
                return true;
            }
            else
            {
                cout << "Target to far away from you. Cannot hit." << endl;
            }
        }
        else
        {
            cout << "Cannot attack another hero without a weapon" << endl;
        }
        return false;
    }

    void Hero::teleport(double x, double y, double z)
    {
        cout << this->name << " was teleported from " << *loc;
        loc->setX(x);
        loc->setY(y);
        loc->setZ(z);
        cout << " to " << *loc << endl;
    }

    void Hero::teleport(const Location& loc)
    {
        this->teleport(loc.getX(), loc.getY(), loc.getZ());
    }

    void Hero::teleport(const Hero& hero)
    {
        this->teleport(*(hero.getLocation()));
    }

    void Hero::setObject(IObject* newObject)
    {
        this->object = newObject;
    }

    void Hero::setHealth(double health)
    {
        this->hp = health;
    }

    string Hero::getName() const
    {
        return name;
    }

    int Hero::getQuest() const
    {
        return quest;
    }

    int Hero::getStrength() const
    {
        return strength;
    }

    int Hero::getAgility() const
    {
        return agility;
    }

    int Hero::getIQ() const
    {
        return intelligence;
    }

    double Hero::getHealth() const
    {
        return hp;
    }

    IObject* Hero::getObject() const
    {
        return object;
    }

    void Hero::setLocation(double dx, double dy)
    {
        loc->add(dx, dy, 0);
        sprite.setPosition({(float)loc->getX(), (float)loc->getY()});
        hitbox = drawHitbox(sprite.getTextureRect(), sprite); //work only when sprite isn't rescaled
    }

    Location* Hero::getLocation() const
    {
        return loc;
    }

    //Graphical part
    sf::RectangleShape& Hero::getHitbox()
    {
        return hitbox;
    }

    sf::Sprite& Hero::getSprite()
    {
        return sprite;
    }

    Animation* Hero::getAnimation() const
    {
        return frames;
    }

    RectangleShape drawHitbox(const IntRect& textRect, const Sprite& sprite)
    {
        RectangleShape rect;
        rect.setFillColor(Color::Transparent);
        rect.setOutlineColor(Color::Black);
        rect.setOutlineThickness(1);
        rect.setSize(Vector2f(textRect.width/2, textRect.height*0.8));
        Vector2f pos = Vector2f(sprite.getPosition().x+rect.getSize().x/2, sprite.getPosition().y+rect.getSize().y*0.2);
        rect.setPosition(pos);
        return rect;
    }

    void Hero::draw(sf::RenderTarget& target, sf::Font& defFont) const
    {
        //target.draw(hitbox); //for debugging
        target.draw(sprite);
        Text nametag(getName(), defFont, 15);
        nametag.setPosition(sprite.getPosition().x+20, sprite.getPosition().y-12);
        target.draw(nametag);
        if(quest>0)
        {
            string qText;
            if(quest==1)
                qText = "Hadena: You can heal yourself with the heal potion or HP icons and even get a speed effect!\n\t\t\t   But be careful the green potion is a poison effect!";
            else if(quest==2)
            {
                if(didBuy)
                    qText = "Shop: Bring the arrows to Gerrin!";
                else
                    qText = "Gerrin: Can you buy me some speed arrows at the shop ? (Blue house)";
            }
            else if(quest==3)
                qText = "Gerrin: Thank you so much. To reward you I'll give you 50HP.";
            else if(quest==4)
                qText = "Gerrin: Wrong item. Go to the shop! (Blue house)";
            else if(quest==5)
                qText = "Shop: Talk to Gerrin and come back!";
            Text q(qText, defFont, 15);
            q.setPosition(10, 10);
            target.draw(q);
        }
    }

    void Hero::setDirection(const sf::Vector2f& dir)
    {
        velocity = dir * (agility*1.0f);
        if(frames!=nullptr)
        {
            Frame* f = frames->getCurrentFrame();
            Dir d = Dir::NONE;
            if(velocity.x > 0)
            {
                d = Dir::RIGHT;
            }
            else if(velocity.x < 0)
            {
                d = Dir::LEFT;
            }
            if(velocity.y > 0)
            {
                d = Dir::FRONT;
            }
            else if(velocity.y < 0)
            {
                d = Dir::BACK;
            }
            if(hp>0)
                f->setDirection(d);
        }
    }

    void Hero::update(World* w, float deltaTime)
    {
        if(object!=nullptr&&object->isInUse())
        {
            //nothing to do for now...
        }
        else
        {
            if(hp>0) //cannot move if dead
            {
                double dx = velocity.x*deltaTime;
                double dy = velocity.y*deltaTime;
                setLocation(dx, dy);
                int collide = w->collideWith(getHitbox());
                if(collide!=CollideMask::HOUSE1)
                    talkToGerrin = false;
                switch(collide) //Collide mask
                {
                    case CollideMask::WALL:
                    {
                        setLocation(-dx, -dy); //rollback if collide with wall
                        break;
                    }
                    case CollideMask::POISON:
                    {
                        hp-=120;
                        if(hp<=0)
                        {
                            frames->getCurrentFrame()->setDirection(Dir::BACK);
                            frames->getCurrentFrame()->setCurrent(AnimType::DEATH);
                        }
                        break;
                    }
                    case CollideMask::SPEED:
                    {
                        agility+=75;
                        break;
                    }
                    case CollideMask::PV:
                    {
                        hp+=50;
                        break;
                    }
                    case CollideMask::ARROW:
                    {
                        Bow* b = dynamic_cast<Bow*>(getObject());
                        if(b!=nullptr)
                        {
                            b->setArrows(b->getArrows()+15);
                        }
                        break;
                    }
                    case CollideMask::HEAL:
                    {
                        hp+=100;
                        break;
                    }
                    case CollideMask::HOUSE2:
                    {
                         quest = 1;
                         break;
                    }
                    case CollideMask::HOUSE1:
                    {
                        if(!talkToGerrin)
                        {
                            talkToGerrin = true;
                            if(quest<2||quest>4)
                            {
                                quest = 2;
                            }
                            else if(quest==2)
                            {
                                if(didBuy)
                                {
                                    quest = 3;
                                    hp+=50;
                                    Game::instance->print("The hero completed the task asked by Gerrin and got 50hp!", true);
                                }
                                else
                                    quest = 4;
                            }
                        }
                        break;
                    }
                    case CollideMask::HOUSE3:
                    {
                        if(quest==2)
                        {
                            didBuy = true;
                        }
                        else
                        {
                            quest = 5;
                            didBuy = false;
                        }
                        break;
                    }
                }
                if(frames!=nullptr)
                {
                    frames->getCurrentFrame()->run = velocity.x != 0 || velocity.y != 0 || frames->getCurrentFrame()->getCurrent()!=AnimType::WALKING;
                }
            }
        }
        if(frames!=nullptr)
        {
            //dont animate the sprite if current is walking but the player isnt walking
            //frames->getCurrentFrame()->run = velocity.x != 0 || velocity.y != 0 || frames->getCurrentFrame()->getCurrent()!=AnimType::WALKING;
            frames->tick(deltaTime, sprite);
        }
    }

    void Hero::useWeapon(float deltaTime, bool pressed)
    {
        if(hp<=0)return; //cannot shoot if dead
        Frame* f = getAnimation()->getCurrentFrame();
        Bow* b = dynamic_cast<Bow*>(getObject());
        if(b!=nullptr)
        {
            if(pressed)
            {
                if(f->getCurrent()!=AnimType::SHOOT)
                {
                    f->setCurrent(AnimType::SHOOT);
                    f->run = true;
                }
                if(!b->isBent())
                {
                    b->tick(deltaTime);
                }
            }
            else
            {
                if(b->isInUse())
                {
                    double power = b->shoot();
                    f->setCurrent(AnimType::WALKING);
                    if(power>0.f)
                    {
                        Vector2f vec = Vector2f(getSprite().getPosition());
                        vec.x+=40.f;
                        vec.y+=35.f;//Heal Speed or Poison (changes the arrow's color
                        new Arrow("Heal", 1, power*10, getAnimation()->getCurrentFrame()->getDirection(), vec);
                    }
                }
            }
        }
    }
}

