#ifndef PARTICLE_H
#define PARTICLE_H

#include "myVectorMath.h"

#include <array>
#include <vector>
#include <iostream>
#include <fstream>

class Particle
{
public:
    Particle (
        std::array<double, 3> pos,
        std::array<double, 3> vel,
        std::array<double, 3> acc,
        double mass );

    std::array<double, 3> pos();
    std::array<double, 3> vel();
    std::array<double, 3> acc();
    double mass();

    void print();
    bool updatePos(std::array<double, 3>, const bool);
    void write_pos_log();
    bool inRegion();

private:
    std::array<double, 3> m_pos;
    std::array<double, 3> m_vel;
    std::array<double, 3> m_acc;
    double m_mass;
    std::vector<std::array<double, 3>> m_pos_log {};
};

#endif
