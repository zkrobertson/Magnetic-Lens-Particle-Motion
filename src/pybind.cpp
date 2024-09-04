#include "pybind.h"

PYBIND11_MODULE(ParticleSimulation, m)
{
    m.doc() = "Charged Particle Path Simulation";
}
