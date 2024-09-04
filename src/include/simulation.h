#ifndef SIMULATION_H
#define SIMULATION_H

#include "myVectorMath.h"

class Simulation 
{
public:
    Simulation(std::string grid_filename, double energy)
    : m_energy{energy}, m_grid_filename{grid_filename}
    {}

    void setGridFilename(const std::string);
    std::string getGridFilename();

private:
    double m_energy;
    std::string m_grid_filename { "/Users/kramer/Documents/CEPPE GRA Projects/LANL Project/code/magfields/VectorField.fld" };
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
        std::string starting_position_function,
        std::vector<double> available_masses,
    ):
        Simulation {grid_filename, energy},
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
