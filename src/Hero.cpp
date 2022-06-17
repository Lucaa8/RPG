#include "Hero.h"

namespace RPG
{
    double const Hero::interactDistance = 7.0;

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

    void Hero::teleport(const Location* loc)
    {
        this->teleport(loc->getX(), loc->getY(), loc->getZ());
    }

    void Hero::teleport(const Hero& hero)
    {
        this->teleport(hero.getLocation());
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
        target.draw(hitbox);
        target.draw(sprite);
        Text nametag(getName(), defFont, 15);
        nametag.setPosition(sprite.getPosition().x+20, sprite.getPosition().y-12);
        target.draw(nametag);
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
            f->setDirection(d);
        }
    }

    void Hero::update(float deltaTime)
    {
        if(object!=nullptr&&object->isInUse())
        {

        }
        else
        {
            loc->add(velocity.x*deltaTime, velocity.y*deltaTime, 0);
            sprite.setPosition({(float)loc->getX(), (float)loc->getY()});
            hitbox = drawHitbox(sprite.getTextureRect(), sprite); //work only when sprite isn't rescaled
            if(frames!=nullptr)
            {
                frames->getCurrentFrame()->run = velocity.x != 0 || velocity.y != 0 || frames->getCurrentFrame()->getCurrent()!=AnimType::WALKING;
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

