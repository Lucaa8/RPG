#include "Frame.h"

//max values: 63       63   1024   1024
int encode(int y, int max, int w, int h)
{
    return (y << 26) | (max << 20) | (w << 10) | h;
}

int* decode(int value)
{
    int* values = new int[4];
    values[0] = (value & 0xFC000000) >> 26;
    values[1] = (value & 0xF00000) >> 20;
    values[2] = (value & 0xFFC00) >> 10;
    values[3] = value & 0x2FF;
    return values;
}

Frame::Frame() : run(false), uid("none"), maxFrames(0), current(0), currentAnimY(0){}

Frame::Frame(string uid, string texturePath)
{
    this->uid = uid;
    if (!texture.loadFromFile(texturePath))
    {
        cout << "Failed to load the " << texturePath << " texture";
        texture.create(64, 64);
    }
    this->maxFrames = -1;
    this->current = 0;
    this->currentAnimY = 0;
    this->frames = nullptr;
    this->setCurrent(AnimType::WALKING);
    this->setDirection(Dir::FRONT);
    this->run = true;
}

Frame::Frame(const Frame& frame)
{
    this->uid = frame.uid;
    this->texture = frame.texture;
    this->maxFrames = frame.maxFrames;
    this->current = frame.current;
    this->currentAnimY = frame.currentAnimY;
    this->currentAnim = frame.currentAnim;
    this->currentDir = frame.currentDir;
    this->frames = new IntRect*[maxFrames];
    for(int i=0;i<maxFrames;i++)
    {
        IntRect r = *(frame.frames[i]);
        this->frames[i] = new IntRect(r.top, r.left, r.width, r.height);
    }
    this->run = run;
}

Frame::~Frame()
{
    deleteFrames();
}

void Frame::apply(Sprite& sprite)
{
    //sprite.setScale({2.0f, 2.0f});
    sprite.setTexture(texture);
    sprite.setTextureRect(*(frames[current]));
}

void Frame::next()
{
    //c un peu du bricolage j'avoue..
    if(current+5>=maxFrames&&getCurrent()==AnimType::SHOOT)return; //when the mouse is still pressed and the player is shooting with a bow, the frame doesnt continue
    current++;
    if(current>=maxFrames)
    {
        current = 0;
    }
}

void Frame::setCurrent(AnimType type)
{
    int* decodeType = decode(type);
    if(decodeType[0] != currentAnimY)
    {
        updateFrames(decodeType[1], decodeType[0], decodeType[2], decodeType[3]);
        this->currentAnim = type;
        this->currentAnimY = decodeType[0];
        this->setDirection(this->getDirection()); //needed to update frames Y coord with the same direction as before
    }
    delete[] decodeType;
}

AnimType Frame::getCurrent() const
{
    return currentAnim;
}

void Frame::setDirection(Dir direction)
{
    if(direction==-1)
    {
        return;
    }
    this->currentDir = direction;
    setY(currentAnimY + direction);
}

Dir Frame::getDirection() const
{
    return currentDir;
}

void Frame::setX(int x)
{
    if(x>=maxFrames)
        return;
    this->current = x;
}

void Frame::setY(int y)
{
    if(maxFrames == -1 || frames[0]->top == y*frames[0]->height)
        return;
    for(int i=0;i<maxFrames;i++)
    {
        frames[i]->top = y*frames[i]->height;
    }
}

void Frame::updateFrames(int max, int y, int w, int h)
{
    if(this->maxFrames != max)
    {
        deleteFrames();
        this->frames = new IntRect*[max];
        for(int i=0;i<max;i++)
        {
            frames[i] = new IntRect(i*w, y*h, w, h);
        }
        this->maxFrames = max;
        this->current = 0;
    }
    else
    {
        for(int i=0;i<max;i++)
        {
            frames[i]->width  = w;
            frames[i]->height = h;
            frames[i]->top = y*h;
        }
    }
}

void Frame::deleteFrames()
{
    if(frames!=nullptr)
    {
        for(int i=0;i<maxFrames;i++)
        {
            delete frames[i];
        }
        delete frames;
    }
}

string Frame::getUid() const
{
    return uid;
}
