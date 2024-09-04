#include "node.h"

#include <iostream>
#include <array>


void Node::print() 
{
    std::cout << "\tPos: " 
        << pos[X] << ',' 
        << pos[Y] << ',' 
        << pos[Z];
    std::cout << "\tMag: " 
        << mag[X] << ',' 
        << mag[Y] << ',' 
        << mag[Z] << '\n';
}

