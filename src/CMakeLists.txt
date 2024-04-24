cmake_minimum_required(VERSION 3.10)

project(IonPathPrediction VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(IonPathPrediction 
    main.cpp 
    node.cpp 
    file_input.cpp 
    myVectorMath.cpp 
    grid.cpp 
    particle.cpp 
    methods.cpp)

target_include_directories(IonPathPrediction PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)
