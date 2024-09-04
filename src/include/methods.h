#ifndef METHODS_H
#define METHODS_H

#include "node.h"
#include "myVectorMath.h"
#include "particle.h"
#include "Random.h"

#include <vector>

namespace Methods 
{


// returns a random position in a rectangle defined by the function
vec defaultRandomPosition();

void monte_carlo(
    std::vector<Node>& grid, 
    Grid::Dimensions& dim, 
    int N, 
    double eV, 
    vec (*rpf)() = defaultRandomPosition, 
    std::string logfile_path = "./monte_carlo_logfile.csv", 
    std::vector<double> available_masses = {1,2,4,14,16,17,18}
);

// NOTE: Optimized single_ion function. Pass Particle as reference
void single_ion(std::vector<Node>& grid, Grid::Dimensions& dim, Particle& particle, const double time_step=1E-8, const bool=false, const bool=false);

}
#endif
