#ifndef METHODS_H
#define METHODS_H

#include "node.h"
#include "myVectorMath.h"
#include "particle.h"
#include "Random.h"

#include <array>

namespace Methods 
{

void monte_carlo(std::vector<Node>& grid, Grid::Dimensions& dim, int N, double eV, double z_center);
void single_ion(std::vector<Node>& grid, Grid::Dimensions& dim, double mass, double eV, double z, double y);

}
#endif
