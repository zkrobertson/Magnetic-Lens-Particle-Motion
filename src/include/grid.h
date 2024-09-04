#ifndef GETINDEX_H
#define GETINDEX_H

#include "myVectorMath.h"
#include "node.h"

#include <vector>

namespace Grid 
{

struct Dimensions
{
    const double X_step;
    const double Y_step;
    const double Z_step;

    const double X_max;
    const double Y_max;
    const double Z_max;

    const std::size_t length {static_cast<std::size_t>((X_max/X_step) + X_step/1) + 1};
    const std::size_t height {static_cast<std::size_t>((Y_max/Y_step) + Y_step/2) + 1};
    const std::size_t width {static_cast<std::size_t>((Z_max/Z_step) + Z_step/2) + 1};

    const std::size_t size { length*width*height };
};

std::size_t getIndex(Dimensions& dim, vec input);
vec get_mag_vector(std::vector<Node>& grid, Dimensions& dim, vec pos);

}

#endif
