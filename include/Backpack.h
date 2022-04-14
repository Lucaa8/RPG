#ifndef BACKPACK_H
#define BACKPACK_H

#include "IObject.h"

#include <stack>
#include <iostream>
using namespace std;

namespace RPG
{
    class Backpack
    {
        public:
            Backpack();
            virtual ~Backpack();
            void pack(IObject*);
            IObject* unpack();
            bool isEmpty() const;

        protected:

        private:
            stack<IObject*> mStack;
    };
}

#endif // BACKPACK_H
