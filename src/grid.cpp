#include "grid.h"

namespace Grid
{

std::size_t getIndex(Dimensions& dim, vec input)
{
    if (input[0]>dim.X_max) input[0] = dim.X_max;
    if (input[1]>dim.Y_max) input[1] = dim.Y_max;
    if (input[2]>dim.Z_max) input[2] = dim.Z_max;

    std::size_t z_steps { static_cast<std::size_t>(input[2] / dim.Z_step + dim.Z_step/2) };
    std::size_t y_steps { static_cast<std::size_t>(input[1] / dim.Y_step + dim.Y_step/2) * dim.width };
    std::size_t x_steps { static_cast<std::size_t>(input[0] / dim.X_step + dim.X_step/2) * dim.width * dim.height };

    return z_steps + y_steps + x_steps;
}

std::array<double, 3> get_mag_vector(std::vector<Node>& grid, Dimensions& dim, vec pos)
{
    // --- Surrounding 8 Points ---
    // The particle is somewhere in the cube defined by these points
    std::array<std::size_t, 8> indices { 
        getIndex(dim, pos),
        getIndex(dim, {pos[0]+dim.X_step, pos[1], pos[2]}),
        getIndex(dim, {pos[0], pos[1]+dim.Y_step, pos[2]}),
        getIndex(dim, {pos[0], pos[1], pos[2]+dim.Z_step}),
        getIndex(dim, {pos[0]+dim.X_step, pos[1], pos[2]+dim.Z_step}),
        getIndex(dim, {pos[0], pos[1]+dim.Y_step, pos[2]+dim.Z_step}),
        getIndex(dim, {pos[0]+dim.X_step, pos[1]+dim.Y_step, pos[2]}),
        getIndex(dim, {pos[0]+dim.X_step, pos[1]+dim.Y_step, pos[2]+dim.Z_step}),
    };

    std::array<double, 8> r;
    double sum_r {0};
    vec mag;

    for (std::size_t i {0};i<8;++i){
        r[i] = Vec::magnitude( pos - grid[indices[i]].pos );
        mag[0] += r[i] * grid[indices[i]].mag[0];
        mag[1] += r[i] * grid[indices[i]].mag[1];
        mag[2] += r[i] * grid[indices[i]].mag[2];
        sum_r += r[i];
    }

    for (double& m : mag){
        m/=sum_r;
    }

    return mag;
}

}
