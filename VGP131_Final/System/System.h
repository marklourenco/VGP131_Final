#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"

#include <iostream>
#include <vector>

using namespace std;

class System
{
public:
    virtual ~System() = default;
    virtual void Update(Entity& entity) = 0;
};

#endif

