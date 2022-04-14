#include "Shield.h"

namespace RPG
{
    Shield::Shield(int solidity) : solidity(solidity) {}

    Shield::~Shield() {}

    string Shield::getName() const
    {
        return "Shield";
    }

    int Shield::getFeature() const
    {
        return solidity;
    }

    string Shield::toString() const
    {
        std::stringstream ss;
        ss << "Shield implements IObject{Solidity=" << getFeature() << "}";
        return ss.str();
    }

    IObject* Shield::clone()
    {
        return new Shield(getFeature());
    }
}
