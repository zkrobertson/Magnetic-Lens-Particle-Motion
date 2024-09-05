# Ion Path Prediction through a Magnetic Lens
Maps the path of an ion through a magnetic field exported from Ansys Maxwell 3D. Simulation code is written in C++ and wrapped by pybind11 to interface with python. This makes it easy to run, access, and plot solutions without having to sacrifice large performance costs.

## Importing 3D Simulation results from Ansys
Given a properly exported data file from Maxwell 3D (.fld file), this code can read, import, and organize the simulation results for use in predicting the path of an ion. The magnetic field is exported as an evenly spaced grid (Although never tested, it should be able to handle non-evenly spaced grids as well). The exported field ought to have the x-axis aligned with the initial motion of the particle (this is an assumption in the C++ code that cannot be accessed with python). Thus the starting position of the ion is at x = 0, on the Y-Z plane.

## Ion Path Prediction
The magnetic field at the point of a particle is estimated by the distance weighted average of the 8 surrounding grid points from the simulation. Using the Lorentz force law, the path of the particle is predicted using Leap-Frog integration. This technique allows the path of the Ion to be modeled in less than 50 steps on average allowing monte-carlo simulations to quickly and efficiently analyze the behavior of the magnetic lens.

## Python scripts
Python scripts are provided to estimate the expected gyro motion of an Ion in a constant B-field and to also help perform post processing on the results. 

# Using Pre-Built Python Library

The pre-built python library is built and available in `bin/`. This static library can be copied into site-packages and used as described below. However, if the C++ source code is altered, modified, or improved the instructions for rebuilding the project are also provided.

# Building Project 

## Prerequisites 

In order to build this project you need a c++ compiler (clang, g++, etc.), cmake, conda, and pybind11 installed in a conda environment.
Pybind11 can be installed with pip, however this distribution does not have the proper .cmake files to build the project and so conda is recommended.

## Installation

Activate a conda environment and clone this repository. You can deactivate the conda environment after you finish building.

``` bash
$ conda create ParticleSimulationPybind11
$ conda activate ParticleSimulationPybind11
$ conda install pybind11 
$ git clone https://github.com/zkrobertson/Magnetic-Lens-Particle-Motion.git
$ cd Magnetic-Lens-Particle-Motion 
$ mkdir build
$ cd build
$ cmake ../src 
$ cmake --build .
$ conda deactivate
```

This will build the python static library (.so file). This file can be copied into the site-packages of a python venv. For example, `./lib/python3.12/site-packages/`. This will make it so that the library can be accessed any where in the virtual environment.

# Python Code Overview

As previously mentioned the C++ code is compiled into a static python library `ParticleSimulation`. The library consists of two classes, one for single ion simulations and another for monte carlo simulations.
The two classes can be imported to python SingleIonSimulation and MonteCarloSimulation

``` python
import ParticleSimulation as ps

newSingleIonSimulation = ps.SingleIonSimulation(grid_filename, energy, mass, starting_position)
newMonteCarloSimulation = ps.MonteCarloSimulation(grid_filename, energy, iterations, starting_position_function, available_masses)
```

These classes both hold energy, and Grid Filename. 
Energy sets the incoming ion energy. 
The Grid Filename is a root path file location of the maxwell 3d exported magnetic field .fld file.
The starting position is a 3-dimensional vector (x,y,z). Common practice is x=0, and the particle enters on Y-Z plane.
The starting position function is a function pointer to a pre-compiled C++ function in the source code. As of now a string is passed in order to determine the proper function. Functions must be written in C++ and added to the header file in order to be called.
The available masses is a list of masses that will randomly be chosen.

After these variables are set the simulation can be run and the results recorded can be read given the provided file location.

``` python
mySimulation.run(resultFile)
results = pd.read(resultFile)
```

The results are saved to a .csv file that is meant to be read by pandas. The run function requires the file path location of the results file. If none is given the simulation is run but only simple data is printed to the console and no ion specific data is saved to a file.
