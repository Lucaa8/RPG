#include "Arrow.h"

namespace RPG
{

    vector<Arrow*> Arrow::arrows;

    int getIndex(vector<Arrow*> vec, Arrow* toFind) {
        int index = -1;
        auto it = find(vec.begin(), vec.end(), toFind);
        if (it != vec.end())
        {
            index = it - vec.begin();
        }
        return index;
    }

    //Size : 64x64
    //Heal location   : x=1 y=1
    //Poison location : x=67 y=1
    //Speed location  : x=1 y=67
    Arrow::Arrow(string effect, int power, float arrowpower, Dir direction, Vector2f pos) : Potion(effect, power), arrowpower(arrowpower), direction(direction)
    {
        if (!sheet.loadFromFile("sprites/arrow.png"))
        {
            cout << "Failed to load the sprites/arrow.png texture";
            sheet.create(64, 64);
        }
        arrow.setPosition(pos);
        arrow.setTexture(sheet);
        arrow.setOrigin(32.f, 32.f);
        IntRect rect;
        if(direction==Dir::LEFT)
        {
            arrow.rotate(180.f);
        }
        else if(direction==Dir::FRONT)
        {
            arrow.rotate(90.f);
        }
        else if(direction==Dir::BACK)
        {
            arrow.rotate(-90.f);
        }
        if(effect == "Heal")
        {
            rect = IntRect(1, 1, 64, 64);
        }
        else if(effect == "Poison")
        {
            rect = IntRect(67, 1, 64, 64);
        }
        else if(effect == "Speed")
        {
            rect = IntRect(1, 67, 64, 64);
        }
        arrow.setTextureRect(rect);
        (Arrow::arrows).push_back(this);
    }

    Arrow::~Arrow()
    {
        remove();
    }

    int getDirX(int dir)
    {
        if(dir==1)
            return -1;
        else if(dir==3)
            return 1;
        return 0;
    }

    int getDirY(int dir)
    {
        if(dir==2)
            return 1;
        else if(dir==0)
            return -1;
        return 0;
    }

    void Arrow::tick(float dt, RenderTarget& target)
    {
        Vector2f pos = arrow.getPosition();
        float vel = dt*arrowpower;
        pos.x += vel*getDirX(direction);
        pos.y += vel*getDirY(direction);
        if(pos.x<-64||pos.x>1280||pos.y<-64||pos.y>720)
        {
            delete this; //call remove() in dtor
            return;
        }
        arrow.setPosition(pos);
        arrow.setScale(0.7f, 0.7f);
        target.draw(arrow);
    }

    void Arrow::remove()
    {
        int index = getIndex(Arrow::arrows, this);
        if(index!=-1)
            (Arrow::arrows).erase((Arrow::arrows).begin()+index);
    }

    float Arrow::getArrowPower() const
    {
        return arrowpower;
    }

    Dir Arrow::getDirection() const
    {
        return direction;
    }

    string Arrow::getName() const
    {
        return "Arrow with Potion effect";
    }

    string Arrow::toString() const
    {
        stringstream ss;
        ss << "Arrow implements Potion implements IObject{Effect=" << getEffect() << ", Power=" << getFeature() << ", ArrowPower=" << getArrowPower() << ", Direction=" << getDirection() << ", X=" << arrow.getPosition().x << ", Y=" << arrow.getPosition().y << "}";
        return ss.str();
    }

    IObject* Arrow::clone()
    {
        return new Arrow(getEffect(), getFeature(), getArrowPower(), getDirection(), arrow.getPosition());
    }
}
