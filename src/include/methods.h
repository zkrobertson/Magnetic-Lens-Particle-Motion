#ifndef METHODS_H
#define METHODS_H

#include "node.h"
#include "grid.h"
#include "myVectorMath.h"
#include "particle.h"
#include "Random.h"

#include <vector>

namespace Methods 
{

// NOTE: **Optimized** single_ion function. Particle passed as reference
void single_ion(
    std::vector<Node>& grid, 
    Grid::Dimensions& dim, 
    Particle& particle, 
    const double time_step, 
    const bool,
    const bool
);


void monte_carlo(
    std::vector<Node>& grid, 
    Grid::Dimensions& dim, 
    int N, 
    double eV, 
    double time_step,
    vec (*rpf)(), 
    std::string logfile_path, 
    std::vector<double> available_masses
);

}
#endif
