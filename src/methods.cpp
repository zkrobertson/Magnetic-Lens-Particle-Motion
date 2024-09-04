#include "config.h"

namespace Methods 
{

// Used to set outer bounds of Random Starting Position
struct rectangle_coordinates
{
    double y_offset;
    double height;
    double z_offset;
    double width;
};

// Used to log starting position of an ion
// Will get phased out for a more comprehensive logging system
struct ion_starting_data
{
    double y;
    double z;
    double mass;
    bool collected;
};

// Used to randomly choose a position within the entrance position
// Switch to struct rectangle_coordinates
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

// TODO: Input should just be a const Grid (Grid dimensions should be a part of grid class) and Particle
// NOTE: Particle is passed by ref
void single_ion(
    std::vector<Node>& grid, 
    Grid::Dimensions& dim, 
    Particle& particle, 
    const double time_step,
    const bool printResults, 
    const bool logResults
)
{
    if (printResults)
    {
        particle.print();
        std::cout << "Running simulation...\n\n";
    }

    int count {0};
    while ( particle.inRegion() && count++ < 1000) particle.updatePos( Grid::get_mag_vector(grid, dim, particle.pos()), time_step );

    if (count >= 1000) 
    {
        std::cerr << "Number of steps reached maximum. Could be caught in propagation loop\n";

        if (!printResults) particle.print(); // if the particle will not be printed then print it here for troubleshooting
    }

    if (printResults)
    {
        std::cout << "Results\n-------\nSteps Taken: " << count << '\n'
            << "Particle Motion Time Elapsed: " << count*time_step/1e-6 << " us" << '\n';
        particle.print();
    }

    if (logResults)
    {
        particle.write_pos_log();
    }

    return;
}

void monte_carlo(
    std::vector<Node>& grid, 
    Grid::Dimensions& dim, 
    int N, 
    double eV, 
    vec (*rpf)(),
    std::string logfile_path,
    std::vector<double> available_masses
)
{
    std::ofstream output { logfile_path };
    output << "x0,y0,z0,vx0,vy0,vz0,x1,y1,z1,vx1,vy1,vz1,mass,pass?\n";

    std::cout << "Running" << std::flush;

    for (int i {0};i<N;++i){

        // --- Random Mass ---
        int index { Random::get(0,std::size(available_masses)) };
        double mass = available_masses[index] * 1.67E-27;

        // --- energy to velocity ---
        double vel_x = sqrt(2 * 1.602e-19 * eV / mass);

        // --- Random Entrance Position ---
        vec start_position { rpf() };

        // --- Create Particle ---
        Particle myIon {
            start_position,       // pos
            {vel_x, 0, 0},        // vel
            {0,0,0},              // acc
            mass
        };

        for (double i : myIon.pos()) output << i << ',';
        for (double i : myIon.vel()) output << i << ',';

        // --- Particle Path Integration ---
        single_ion(grid, dim, myIon);

        for (double i : myIon.pos()) output << i << ',';
        for (double i : myIon.vel()) output << i << ',';

        output << mass/1.67E-27 << ',' << 0 << '\n';

        // --- Loading Bar ---
        if (i%(N/3) == 0) std::cout << '.' << std::flush;
    }
    std::cout << '\n';

    output.close();
}

}
