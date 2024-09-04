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
    Simulation(std::string grid_filename, double energy)
    : m_energy{energy}, 
        m_grid_filename{grid_filename}, 
        m_dimensions { read_file_header(grid_filename) }, // Throw Invalid Dimensions Error in this function
        m_grid { import_file(grid_filename) }
    {

    }

    void setGridFilename(const std::string);
    std::string getGridFilename();

// So derived classes can access these members
protected:
    Grid::Dimensions m_dimensions;
    std::vector<Node> m_grid;
    double m_energy;

private:
    std::string m_grid_filename;
};

class SingleIonSimulation : public Simulation
{
public:
    SingleIonSimulation(
        std::string grid_filename,
        double energy, 
        double mass, 
        vec starting_position
    ):
        Simulation {grid_filename, energy},
        m_mass{mass},
        m_starting_position{starting_position}
    {

    }

    void run(const std::string results_filename);

private:
    double m_mass;
    vec m_starting_position;
};

class MonteCarloSimulation : public Simulation
{
public:
    MonteCarloSimulation(
        std::string grid_filename,
        double energy, 
        int iterations,
        std::string starting_position_function,
        std::vector<double> available_masses
    ):
        Simulation {grid_filename, energy},
        m_monte_carlo_iterations{iterations},
        m_starting_position_function{starting_position_function},
        m_available_masses{available_masses}
    {

    }

    void run(const std::string results_filename);

private:
    int m_monte_carlo_iterations;
    std::string m_starting_position_function;
    std::vector<double> m_available_masses;
};

#endif
