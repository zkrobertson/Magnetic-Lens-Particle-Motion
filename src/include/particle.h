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
        double mass
    );

    std::array<double, 3> pos();
    std::array<double, 3> vel();
    std::array<double, 3> acc();
    double mass();

    bool get_save_trajectory();
    void set_save_trajectory(const bool);

    void print();
    bool updatePos(std::array<double, 3>);
    void write_pos_log();
    bool inRegion();

private:
    std::array<double, 3> m_pos;
    std::array<double, 3> m_vel;
    std::array<double, 3> m_acc;
    double m_mass;
    // NOTE: Should we really log the particles postition? 
    // this might take up a lot of space and might be better done externally
    std::vector<std::array<double, 3>> m_pos_log {};
    bool m_save_trajectory = false;
};

#endif
