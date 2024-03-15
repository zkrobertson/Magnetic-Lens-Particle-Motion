#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <array>

struct Node 
{
    std::array<double,3> pos;
    std::array<double,3> mag;

    enum Coordinates
    {
        X,
        Y,
        Z
    };

    void print();
};

#endif
