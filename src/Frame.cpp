#include "Frame.h"

Frame::Frame() : run(false), uid("none"), maxFrames(0), current(0){}

Frame::Frame(string uid, string texturePath, int maxFrames, int y, int w, int h)
{
    this->uid = uid;
    if (!texture.loadFromFile(texturePath))
    {
        cout << "Failed to load the " << texturePath << " texture";
        texture.create(64, 64);
    }
    this->maxFrames = maxFrames;
    this->current = 0;
    this->frames = new IntRect*[maxFrames];
    for(int i=0;i<maxFrames;i++)
    {
        frames[i] = new IntRect(i*w, y*h, w, h);
    }
    this->run = true;
}

Frame::Frame(const Frame& frame)
{
    this->uid = frame.uid;
    this->texture = frame.texture;
    this->maxFrames = frame.maxFrames;
    this->current = frame.current;
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
    if(frames!=nullptr)
    {
        for(int i=0;i<maxFrames;i++)
        {
            delete frames[i];
        }
        delete frames;
    }
}

void Frame::apply(Sprite& sprite)
{
    sprite.setScale({2.0f, 2.0f});
    sprite.setTexture(texture);
    sprite.setTextureRect(*(frames[current]));
}

void Frame::next()
{
    current++;
    if(current>=maxFrames)
    {
        current = 0;
    }
}

void Frame::setFrameY(int y)
{
    for(int i=0;i<maxFrames;i++)
    {
        frames[i]->top = y*frames[i]->height;
    }
}

void Frame::setFrameX(int x)
{
    this->current = x;
}

string Frame::getUid() const
{
    return uid;
}
