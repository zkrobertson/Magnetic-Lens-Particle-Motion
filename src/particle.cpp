#include "particle.h"

#include <array>
#include <iostream>
#include <fstream>

// TODO: Particle should hold initial position (unless the particle motion is logged then index [0] is initial position)

Particle::Particle (
    vec pos,
    vec vel,
    vec acc,
    double mass
) : m_pos { pos }
    , m_vel { vel }
    , m_acc { acc }
    , m_mass { mass }
{ 
    m_pos_log.emplace_back(m_pos); 

    if (mass > 0.5){
        m_mass = mass*1.66e-27;
    }
}

vec Particle::pos() { return m_pos; }
vec Particle::vel() { return m_vel; }
vec Particle::acc() { return m_acc; }
double Particle::mass() { return m_mass; }

bool Particle::get_save_trajectory(){ return m_save_trajectory; }
void Particle::set_save_trajectory(const bool b) { m_save_trajectory = b; }

void Particle::print()
{
    std::cout << "Mass: " << m_mass << " \n"
        << "Pos: " << m_pos << '\n'
        << "Vel: " << m_vel << '\n'
        << "Acc: " << m_acc << '\n';

    if (m_save_trajectory) std::cout << "Saving Trajectory\n";
    else std::cout << "Not Saving Trajectory\n";
}

// Leap-Frog Integration
bool Particle::updatePos(const vec B, const double dt)
{
    vec vxb = Vec::cross(m_vel, B);

    for (std::size_t i {0};i<3;++i){
        m_pos[i] = m_pos[i] + m_vel[i] * dt + 0.5 * m_acc[i] * dt * dt;
        vxb[i] = vxb[i] * 1.602E-19 / m_mass;
        m_vel[i] = m_vel[i] + (vxb[i] + m_acc[i])/2 * dt;
    }

    m_acc = vxb;

    // Log positions for single_ion_path
    if (m_save_trajectory)
        m_pos_log.emplace_back(m_pos);

    return inRegion();
}

// NOTE: should the output file always be single_ion_path.csv? 
// Think the filename should be an argument maybe with a the default as single_ion_path
void Particle::write_pos_log()
{
    std::ofstream outf { "single_ion_path.csv" };
    for (vec& pos : m_pos_log)
    {
        outf << pos << '\n';
    }
}

// TODO: These should be bound by grid dimensions or at least passed in as arguments
bool Particle::inRegion()
{
    if (m_pos[0] < 0 || m_pos[0] > 0.63){
        return false;
    }
    if (m_pos[1] < 0 || m_pos[1] > 0.010){
        return false;
    }
    if (m_pos[2] < 0 || m_pos[2] > 0.140){
        return false;
    }
    return true;
}

bool Particle::passed()
{
    if (m_pos[0] < 0 && m_pos[1] < 0.010 && m_pos[1] > 0.0 && m_pos[2] > 0.010 && m_pos[2] < 0.125)
        return true;
    return false;
}
