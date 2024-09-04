#ifndef PARTICLE_H
#define PARTICLE_H

#include "myVectorMath.h"

#include <vector>

class Particle
{
public:
    Particle (
        vec pos,
        vec vel,
        vec acc,
        double mass
    );

    vec pos();
    vec vel();
    vec acc();
    double mass();

    bool get_save_trajectory();
    void set_save_trajectory(const bool);

    void print();
    bool updatePos(vec, const double);
    void write_pos_log();
    bool inRegion();

private:
    vec m_pos;
    vec m_vel;
    vec m_acc;
    double m_mass;

    // NOTE: Should we really log the particles postition? 
    // this might take up a lot of space
    std::vector<vec> m_pos_log {};
    bool m_save_trajectory = false;
};

#endif
