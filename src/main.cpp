#include "config.h"

#include <iostream>
#include <thread>

struct simulation 
{
    std::string method {};
    std::string filename { "/Users/kramer/Documents/CEPPE GRA Projects/LANL Project/code/magfields/VectorField.fld" };
    double energy { 500 };
    int monte_carlo_iterations { 10000 };
    double hole_center_z { 0.001 }; 
    double single_ion_y { 0.005 };
    double single_ion_z { 0.001 };
    double mass { 1 };
};

void setSimulation(simulation& sim)
{
    // Read setting file 
    //
    // --- FORMAT ---
    // 1. vector field filename
    // 2. method 
    // 3. energy 
    // 4. logfile name (optional)

    // If the method is Monte Carlo Simulation
    // 1. Number of Iterations
    // 2. Available Masses (optional)
    // 3. RandomPositionFunction (optional)

    // If the method is Just a Single Ion
    // 1. position (x,y,z)
    // 2. mass
}

int main(int argc, char* argv[])
{
    simulation mySimulation;

    // There has to be a better way to do this. I am thinking these can be set in a setting file that can be created with a python script
    for (int i {1};i<argc;++i)
    {
        if ( strcmp(argv[i], "-f") == 0 ){
            mySimulation.filename = argv[i+1];
        } else if ( strcmp(argv[i], "-m") == 0 ){
            mySimulation.method = argv[i+1];
        } else if ( strcmp(argv[i], "-eV") == 0 ){
            std::stringstream energy_buff;
            energy_buff << argv[i+1];
            energy_buff >> mySimulation.energy;
        } else if (mySimulation.method == "monte" && strcmp(argv[i], "-N") == 0 ){
            std::stringstream monte_carlo_iterations_buff;
            monte_carlo_iterations_buff << argv[i+1];
            monte_carlo_iterations_buff >> mySimulation.monte_carlo_iterations;
        } else if (mySimulation.method == "monte" && strcmp(argv[i], "-z") == 0 ){
            std::stringstream hole_center_z_buff;
            hole_center_z_buff << argv[i+1];
            hole_center_z_buff >> mySimulation.hole_center_z;
        } else if (mySimulation.method == "single" && strcmp(argv[i], "-y") == 0 ){
            std::stringstream single_ion_y_buff;
            single_ion_y_buff << argv[i+1];
            single_ion_y_buff >> mySimulation.single_ion_y;
        } else if (mySimulation.method == "single" && strcmp(argv[i], "-z") == 0 ){
            std::stringstream single_ion_z_buff;
            single_ion_z_buff << argv[i+1];
            single_ion_z_buff >> mySimulation.single_ion_z;
        } else if (mySimulation.method == "single" && strcmp(argv[i], "-mass") == 0 ){
            std::stringstream mass_buff;
            mass_buff << argv[i+1];
            mass_buff >> mySimulation.mass;
        } 
    }

    Grid::Dimensions dimensions { read_file_header(mySimulation.filename) };
    if (dimensions.size <= 1)
    {
        std::cerr << "Invalid Dimensions or they could not be determine\n";
        return 1;
    }

    std::vector<Node> grid { import_file(mySimulation.filename) }; 

    if (mySimulation.method == "single"){

        // Output a description
        std::cout << "Running a single ion\n";
        std::cout << "\tMass: " << mySimulation.mass << '\n'
            << "\tEnergy: " << mySimulation.energy << '\n'
            << "\t(Z,Y): (" << mySimulation.single_ion_z << ',' << mySimulation.single_ion_y << ")\n";

        // Convert mass and velocity to proper units (kg, m/s)
        mySimulation.mass *= 1.67E-27;
        double vel_x = sqrt(2 * 1.602e-19 * mySimulation.energy / mySimulation.mass);

        // Initial state is defined on initialization and cannot be changed
        // position changes with updatePos(given vector field)
        Particle myIon {
            {0, mySimulation.single_ion_y, mySimulation.single_ion_z},
            {vel_x, 0, 0},
            {0,0,0},
            mySimulation.mass
        };

        // myIon is passed by reference and the position is modified by propogating it through the b-field
        Methods::single_ion(grid, dimensions, myIon);
        // Can access the new position of myIon here

    } else if (mySimulation.method == "monte"){
        std::cout << "Running a monte carlo simulation\n"
            << "\tNumber of Samples: " << mySimulation.monte_carlo_iterations << '\n'
            << "\tEnergy: " << mySimulation.energy << '\n';

        // NOTE: Optionally pass a function to return a random starting position
        // default is defaultRandomPosition(y_offset=0, height=10, z_offset=1E-3, width=1)
        Methods::monte_carlo(grid, dimensions, mySimulation.monte_carlo_iterations, mySimulation.energy);

    }

    return 0;
}

