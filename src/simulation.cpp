#include "simulation.h"
#include "methods.h"
#include "particle.h"
#include "randomPosition.h"

#include <iostream>

void Simulation::setGridFilename(const std::string filename){ m_grid_filename = filename; }
std::string Simulation::getGridFilename(){ return m_grid_filename; }

// TODO: ADD time step, print to console boolean, and log boolean + log filename
void SingleIonSimulation::run(const std::string results_filename)
{
    // if a results_filename is not given the default must be true and so print output to console
    bool console_output {false};
    if (!results_filename.compare("print_to_console"))
    {
        // Output a Simulation description to the console
        std::cout << "Running a single ion\n";
        std::cout << "\tMass: " << m_mass << '\n'
            << "\tEnergy: " << m_energy << '\n'
            << "\t(Z,Y): (" << m_starting_position[2] << ',' << m_starting_position[1] << ")\n";
        console_output = true;
    }

    // Convert mass and velocity to proper units (kg, m/s)
    m_mass *= 1.67E-27;
    double vel_x = sqrt(2 * 1.602e-19 * m_energy / m_mass);

    // Initial state is defined on initialization and cannot be changed
    // position only changes with updatePos(given vector field)
    Particle myIon {
        m_starting_position,
        {vel_x, 0, 0},
        {0,0,0},
        m_mass
    };

    // NOTE: logging is done with two different methods...
    if (!console_output) myIon.set_log_filename(results_filename);

    // myIon is passed by reference and the position is modified by propogating it through the b-field
    Methods::single_ion(m_grid, m_dimensions, myIon, m_time_step, console_output, !console_output);
    // Can access the new position of myIon here

}

void MonteCarloSimulation::run(const std::string results_filename)
{
    std::cout << "Running a monte carlo simulation\n"
        << "\tNumber of Samples: " << m_monte_carlo_iterations << '\n'
        << "\tEnergy: " << m_energy << '\n';

    vec (*rpf)();
    if (!m_starting_position_function.compare("default"))
        rpf = defaultRandomPosition;
    // else if the string equals a different function defined in randomPosition.h

    // NOTE: Optionally pass a function to return a random starting position
    // default is defaultRandomPosition(y_offset=0, height=10E-3, z_offset=1E-3, width=1)

    Methods::monte_carlo(m_grid, 
                         m_dimensions, 
                         m_monte_carlo_iterations, 
                         m_energy, 
                         rpf,
                         results_filename,
                         m_available_masses);
}
