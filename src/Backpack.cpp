#include "Backpack.h"

namespace RPG
{
    Backpack::Backpack(){}

    Backpack::~Backpack(){}

    void Backpack::pack(IObject* obj)
    {
        mStack.push(obj);
    }

    IObject* Backpack::unpack()
    {
        IObject* o = mStack.top();
        mStack.pop();
        return o;
    }

    bool Backpack::isEmpty() const
    {
        return mStack.empty();
    }
}
