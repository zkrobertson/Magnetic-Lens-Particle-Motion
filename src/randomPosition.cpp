#include "randomPosition.h"
#include "Random.h"

// Used to randomly choose a position within the entrance position
// TODO: Switch to struct rectangle_coordinates and make it accessible from python
vec defaultRandomPosition()
{
    double y_offset {0.0};
    double height   {10E-3};
    double z_offset {1E-3};
    double width    {1E-3};

    double y { static_cast<double>(Random::get(0, 10000)) * 1E-4 * height + y_offset };
    double z { static_cast<double>(Random::get(0, 10000)) * 1E-4 * width  + z_offset };

    return vec { 0.0, y, z };
}
