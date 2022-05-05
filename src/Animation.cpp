#include "Animation.h"

Animation::Animation() : frameTime(0.1f), currTime(0.1f), currFrame(nullptr), frames(nullptr), framesSize(0) {}

Animation::Animation(float time) : frameTime(time), currTime(time), currFrame(nullptr), frames(nullptr), framesSize(0) {}

Animation::~Animation()
{
    //no need to delete currFrame because the frame is in the frames array
    if(frames!=nullptr)
    {
        for(int i=0;i<framesSize;i++)
        {
            delete frames[i];
        }
        delete frames;
    }
}

void Animation::setCurrentFrame(string frameUid)
{
    for(int i=0;i<framesSize;i++)
    {
        if((frames[i])->getUid() == frameUid)
        {
            this->currFrame = frames[i];
        }
    }
}

Frame* Animation::getCurrentFrame() const
{
    return currFrame;
}

void Animation::setFrames(Frame** f, int size)
{
    if(frames!=nullptr)
    {
        for(int i=0;i<framesSize;i++)
        {
            delete frames[i];
        }
        delete frames;
    }
    this->framesSize = size;
    frames = new Frame*[size];
    for(int i=0;i<size;i++)
    {
        frames[i] = f[i];
    }
    currFrame = frames[0];
}

void Animation::tick(float deltaTime, Sprite& s)
{
    if(currFrame==nullptr)return;
    if(!(currFrame->run))
    {
        currTime = frameTime;
    }
    else
    {
        currTime -= deltaTime;
        if(currTime <= 0)
        {
            currFrame->next();
            currTime = frameTime;
        }
    }
    currFrame->apply(s);
}

Animation* Animation::clone() const
{
    Animation* a = new Animation();
    a->frameTime = frameTime;
    a->currTime = currTime;
    a->framesSize = framesSize;
    a->frames = new Frame*[a->framesSize];
    for(int i=0;i<a->framesSize;i++)
    {
        a->frames[i] = new Frame(*(frames[i]));
    }
    a->currFrame = a->frames[0];
    return a;
}

