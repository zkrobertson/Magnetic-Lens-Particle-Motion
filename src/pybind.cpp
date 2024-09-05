#include "pybind.h"
#include "myVectorMath.h"
#include "simulation.h"


PYBIND11_MODULE(ParticleSimulation, m)
{
    m.doc() = "Charged Particle Path Simulation";

    // ARGUMENTS: grid filename, energy, time step, mass, starting position
    py::class_<SingleIonSimulation>(m, "SingleIon")
        .def(py::init<std::string, double, double, double, vec>()) 
        .def("run", &SingleIonSimulation::run);

    // ARGUMENTS: grid filename, energy, time_step, random position function, available masses
    py::class_<MonteCarloSimulation>(m, "MonteCarlo")
        .def(py::init<std::string, double, double, int, std::string, std::vector<double>>()) 
        .def("run", &MonteCarloSimulation::run);
}
