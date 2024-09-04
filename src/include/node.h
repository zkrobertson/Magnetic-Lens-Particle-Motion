#ifndef NODE_H
#define NODE_H

#include "myVectorMath.h"

struct Node 
{
    vec pos;
    vec mag;
    // TODO: Add electric field

    // NOTE: kinda not super useful?
    enum Coordinates
    {
        X,
        Y,
        Z
    };

    void print();
};

#endif
