#ifndef SIMULATION_H
#define SIMULATION_H

#include "myVectorMath.h"
#include "grid.h"
#include "file_input.h"

#include <string>
#include <vector>

class Simulation 
{
public:
    Simulation(std::string grid_filename, double energy, double time_step)
    : m_grid_filename{grid_filename}, 
        m_energy{energy}, 
        m_time_step { time_step },
        m_dimensions { read_file_header(grid_filename) }, // Throw Invalid Dimensions Error in this function
        m_grid { import_file(grid_filename) }
    {

    }

    // TODO: make sure these functions import header and grid when file is changed
    void setGridFilename(const std::string); // Use these to redo filename setting 
    std::string getGridFilename();

// Protected so derived classes can access these members
protected:
    Grid::Dimensions m_dimensions;
    std::vector<Node> m_grid;
    double m_energy;
    double m_time_step;

private:
    std::string m_grid_filename;
};

// ------------------------------------------

class SingleIonSimulation : public Simulation
{
public:
    SingleIonSimulation(
        std::string grid_filename,
        double energy, 
        double time_step,
        double mass, 
        vec starting_position
    ):
        Simulation {grid_filename, energy, time_step},
        m_mass{mass},
        m_starting_position{starting_position}
    {
    }

    // If a filename is given the results get wrttien to the filename given
    // If a filename is not given the output is a summary written to the console
    void run(const std::string results_filename);

private:
    double m_mass;
    vec m_starting_position;
};

// ------------------------------------------

// TODO: Need to implament use of starting position function and available available_masses
// also need input for time_step (should be a member of parent Simulation)
class MonteCarloSimulation : public Simulation
{
public:
    MonteCarloSimulation(
        std::string grid_filename,
        double energy, 
        double time_step,
        int iterations,
        std::string starting_position_function,
        std::vector<double> available_masses
    ):
        Simulation {grid_filename, energy, time_step},
        m_monte_carlo_iterations{iterations},
        m_starting_position_function{starting_position_function},
        m_available_masses{available_masses}
    {
    }

    // Filename must be provided to run simulation and log results
    void run(const std::string results_filename);

private:
    int m_monte_carlo_iterations;
    std::string m_starting_position_function;
    std::vector<double> m_available_masses;
};

#endif
