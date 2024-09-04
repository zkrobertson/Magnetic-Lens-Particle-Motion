#include "pybind.h"
#include "myVectorMath.h"
#include "simulation.h"


PYBIND11_MODULE(ParticleSimulation, m)
{
    m.doc() = "Charged Particle Path Simulation";

    py::class_<SingleIonSimulation>(m, "SingleIon")
        .def(py::init<std::string, double, double, vec>())
        .def("run", &SingleIonSimulation::run);

    py::class_<MonteCarloSimulation>(m, "MonteCarlo")
        .def(py::init<std::string, double, std::string, std::vector<double>>())
        .def("run", &MonteCarloSimulation::run);
}
