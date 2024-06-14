#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <vector>

using namespace std;

class Component
{
private:
    int id;
public:
    Component() {
        static int next_id = 0;
        id = next_id++;
    }
    virtual ~Component() = default;
    int getID() {
        return id;
    }
    virtual void PrintComponent() = 0;
};

#endif