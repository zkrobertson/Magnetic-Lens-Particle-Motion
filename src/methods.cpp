#include "config.h"

namespace Methods 
{

struct ion_starting_data
{
    double y;
    double z;
    double mass;
    bool collected;
};

void monte_carlo(std::vector<Node>& grid, Grid::Dimensions& dim, int N, double eV, double z_center)
{
    std::vector<Particle> finishing_positions {};
    std::vector<ion_starting_data> starting_positions {};
    std::array<double, 7> available_masses { 1,2,4,14,16,17,18 };

    
    std::cout << "Running" << std::flush;

    for (int i {0};i<N;++i){

        // --- Random Mass ---
        int index { Random::get(0,6) };
        double mass = available_masses[index] * 1.67E-27;

        // --- fluxuation in energy ---
        double vel_x = sqrt(2 *1.602e-19 * (eV + static_cast<double>(Random::get(0,5))) / mass);

        // --- Random Entrance Position ---
        double y { static_cast<double>(Random::get(0, 10000)) * 10E-7 };
        double z { static_cast<double>(Random::get(0, 10000)) * 1E-7 + 1E-3};

        Particle myIon {
            {0.0, y, z},          // pos
            {vel_x, 0, 0},        // vel
            {0,0,0},              // acc
            mass
        };

        // --- Particle Path Integration ---
        int count {0};
        while ( myIon.inRegion() && count++ < 10000) myIon.updatePos( Grid::get_mag_vector(grid, dim, myIon.pos()), false );

        // --- Ion Passed through to the Collection Screen ---
        if (myIon.pos()[0] < 0) finishing_positions.emplace_back( myIon );

        // --- Ion Starting Positions logged with whether it passed or not ---
        starting_positions.emplace_back( ion_starting_data { y, z, mass, myIon.pos()[0] < 0 } );

        // --- Loading Bar ---
        if (i%(N/3) == 0) std::cout << '.' << std::flush;
    }
    std::cout << '\n';

    std::ofstream final { "final_positions.csv" };
    for (Particle& ion : finishing_positions)
    {
        final << ion.mass()/1.67E-27 << ',' << ion.pos() << '\n';
    }
    final.close();

    std::ofstream starting { "starting_positions.csv" };
    for (ion_starting_data& ion : starting_positions)
    {
        starting << ion.mass/1.67E-27 << ',' << ion.y << ',' << ion.z << ',' << ion.collected << '\n';
    }
    starting.close();

    std::cout << "Out of " << N << " ions " << size(finishing_positions) << " passed." << '\n';
    std::cout << "Pass Efficiency = " << size(finishing_positions) / static_cast<double>(N) << '\n';
}

void single_ion(std::vector<Node>& grid, Grid::Dimensions& dim, double mass, double eV, double z, double y)
{
    mass *= 1.67E-27;
    double vel_x = sqrt(2 * 1.602e-19 * eV / mass);

    Particle myIon {
        {0, y, z},
        {vel_x, 0, 0},
        {0,0,0},
        mass
    };

    myIon.print();
    std::cout << "Running simulation...\n\n";

    int count {0};
    while ( myIon.inRegion() && count++ < 10000) myIon.updatePos( Grid::get_mag_vector(grid, dim, myIon.pos()), true );

    std::cout << "Results\n-------\nSteps Taken: " << count << '\n'
        << "Time Elapsed: " << count*DT << '\n';
    myIon.print();
    myIon.write_pos_log();
}

}
