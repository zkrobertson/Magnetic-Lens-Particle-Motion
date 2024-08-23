#ifndef METHODS_H
#define METHODS_H

#include "node.h"
#include "myVectorMath.h"
#include "particle.h"
#include "Random.h"

#include <array>

namespace Methods 
{

// NOTE: Monte Carlo should run the single_ion function N times
// Which means it needs to handle random starting position and random mass and then run single_ion
// It also needs to log all the ions (Log file needs a name... or return an array of length(N) which seems a bit over the top)
void monte_carlo(std::vector<Node>& grid, Grid::Dimensions& dim, int N, double eV, double z_center);

// NOTE: Optimize single_ion function. Pass Particle as reference
void single_ion(std::vector<Node>& grid, Grid::Dimensions& dim, Particle& particle);

}
#endif
