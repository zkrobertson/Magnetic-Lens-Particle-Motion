#include "methods.h"
#include "randomPosition.h"

namespace Methods 
{

#define MAX_NUM_STEPS 50000

// NOTE: Particle is passed by ref
// Time step is default 1e-8
// and print and log are default false
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
        std::cout << "Initial State of particle:\n";
        particle.print();
        std::cout << "Running simulation...\n\n";
    }

    int count {0};
    while ( particle.inRegion(dim) && count++ < MAX_NUM_STEPS) 
    {
        /*
        std::cout << "\n---New Particle Step---\n";
        particle.print();
        std::cout << "Vmag: " << Vec::magnitude(m_vel) << "\n\n";
        */

        particle.updatePos( Grid::get_mag_vector(grid, dim, particle.pos()), time_step );
    }

    if (count >= MAX_NUM_STEPS) 
    {
        std::cerr << "Number of steps reached maximum. Could be caught in endless loop\n";
        if (!printResults) particle.print(); // if the particle will not be printed then print it here for troubleshooting
    }

    if (printResults)
    {
        std::cout << "Results\n-------\nSteps Taken: " << count << '\n'
            << "Particle Motion Time Elapsed: " << count*time_step/1e-6 << " us" << '\n';
        std::cout << "Particle ";

        if (particle.passed(dim))
            std::cout << "passed\n"; 
        else 
            std::cout << "failed to pass\n";

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
    double time_step,
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
        int index { Random::get(0,std::size(available_masses)-1) };
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
        single_ion(grid, dim, myIon, time_step, false, false);

        for (double i : myIon.pos()) output << i << ',';
        for (double i : myIon.vel()) output << i << ',';

        output << mass/1.67E-27 << ',';
        output << myIon.passed(dim) << '\n';

        // --- Loading Bar ---
        if (i%(N/3) == 0) std::cout << '.' << std::flush;
    }
    std::cout << '\n';

    output.close();
    std::cout << "Simulation Complete. Results written too:\n" << logfile_path << '\n';
}

}
