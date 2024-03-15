#include "config.h"

#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::string filename { "Fillets.fld" };
    std::string method {};
    double energy {500};
    int monte_carlo_iterations {10000};
    double hole_center_z { 0.012 }; 
    double single_ion_y {0.0125};
    double single_ion_z {0.01};
    double mass {1};

    for (int i {1};i<argc;++i)
    {
        if ( strcmp(argv[i], "-f") == 0 ){
            filename = argv[i+1];
        } else if ( strcmp(argv[i], "-m") == 0 ){
            method = argv[i+1];
        } else if ( strcmp(argv[i], "-eV") == 0 ){
            std::stringstream energy_buff;
            energy_buff << argv[i+1];
            energy_buff >> energy;
        } else if (method == "monte" && strcmp(argv[i], "-N") == 0 ){
            std::stringstream monte_carlo_iterations_buff;
            monte_carlo_iterations_buff << argv[i+1];
            monte_carlo_iterations_buff >> monte_carlo_iterations;
        } else if (method == "monte" && strcmp(argv[i], "-z") == 0 ){
            std::stringstream hole_center_z_buff;
            hole_center_z_buff << argv[i+1];
            hole_center_z_buff >> hole_center_z;
        } else if (method == "single" && strcmp(argv[i], "-y") == 0 ){
            std::stringstream single_ion_y_buff;
            single_ion_y_buff << argv[i+1];
            single_ion_y_buff >> single_ion_y;
        } else if (method == "single" && strcmp(argv[i], "-z") == 0 ){
            std::stringstream single_ion_z_buff;
            single_ion_z_buff << argv[i+1];
            single_ion_z_buff >> single_ion_z;
        } else if (method == "single" && strcmp(argv[i], "-mass") == 0 ){
            std::stringstream mass_buff;
            mass_buff << argv[i+1];
            mass_buff >> mass;
        } 
    }

    Grid::Dimensions dimensions { read_file_header(filename) };
    if (dimensions.size <= 1)
    {
        std::cerr << "Invalid Dimensions or they could not be determine\n";
        return 1;
    }

    std::vector<Node> grid { import_file(filename) }; 

    if (method == "single"){
        std::cout << "Running a single ion\n";
        std::cout << "\tMass: " << mass << '\n'
            << "\tEnergy: " << energy << '\n'
            << "\t(Z,Y): (" << single_ion_z << ',' << single_ion_y << ")\n";
        Methods::single_ion(grid, dimensions, mass, energy, single_ion_z, single_ion_y);

    } else if (method == "monte"){
        std::cout << "Running a monte carlo simulation\n"
            << "\tNumber of Samples: " << monte_carlo_iterations << '\n'
            << "\tEnergy: " << energy << '\n';
        Methods::monte_carlo(grid, dimensions, monte_carlo_iterations, energy, hole_center_z);

    }

    return 0;
}

