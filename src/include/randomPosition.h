#ifndef RANDOMPOSITION_H
#define RANDOMPOSITION_H

#include "myVectorMath.h"

// Used to set outer bounds of Random Starting Position
struct rectangle_coordinates
{
    double y_offset;
    double height;
    double z_offset;
    double width;
};

vec defaultRandomPosition();

#endif
