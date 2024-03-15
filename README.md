# Ion Path Prediction through a Magnetic Lens
Maps the path of an ion through a magnetic field exported from Ansys Maxwell 3D. The magentic fields were designed, simulated and analyzed by myself to meet the project criteria. I then wrote this C++ code to analyze the behavior of the magnetic field using monte-carlo simulations.

## Importing 3D Simulation results from Ansys
Given a properly exported data file from Maxwell 3D, this code can read, import, and organize the simulation results for use in predicting the path of an ion. The magnetic field is exported as an evenly spaced grid (Although never tested, it should be able to handle non-evenly spaced grids as well).

## Ion Path Prediction
The magnetic field at the point of a particle is estimated by the distance weighted average of the 8 surrounding grid points from the simulation. Using the Lorentz force law, the path of the particle is predicted using Leap-Frog integration. This technique allows the path of the Ion to be modeled in less than 50 steps on average allowing for monte-carlo simulations to be extremly quick and efficient to analyze the behavior of the magnetic lens.
