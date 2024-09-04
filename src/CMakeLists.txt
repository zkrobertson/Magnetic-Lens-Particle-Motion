cmake_minimum_required(VERSION 3.15)

project(PyBind11_ParticleSimulation VERSION 2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

pybind11_add_module(ParticleSimulation 
    node.cpp 
    file_input.cpp 
    myVectorMath.cpp 
    grid.cpp 
    particle.cpp 
    methods.cpp
    simulation.cpp
)

target_include_directories(ParticleSimulation PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)
install(TARGETS example DESTINATION .)
