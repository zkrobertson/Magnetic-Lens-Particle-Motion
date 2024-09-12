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
void Particle::set_log_filename(const std::string filename) 
{ 
    m_save_trajectory = true;
    // TODO: Verify file path?
    m_log_filename = filename;
}

void Particle::print()
{
    std::cout << "Mass: " << m_mass << " \n"
        << "Pos: " << m_pos << '\n'
        << "Vel: " << m_vel << '\n'
        << "Acc: " << m_acc << '\n';
    std::cout << "Vmag: " << Vec::magnitude(m_vel) << '\n';

    return;
    if (m_save_trajectory) std::cout << "Saving Trajectory\n";
    else std::cout << "Not Saving Trajectory\n";
}

// Leap-Frog Integration
void Particle::updatePos(const vec B, const double dt)
{
    vec vxb = Vec::cross(m_vel, B);

    for (auto& i : vxb)
    {
        i = i * 1.602E-19 / m_mass;
    }

    for (std::size_t i {0};i<3;++i){
        m_pos[i] = m_pos[i] + m_vel[i] * dt + 0.5 * m_acc[i] * dt * dt;
        m_vel[i] = m_vel[i] + (vxb[i] + m_acc[i])/2 * dt;
    }

    /*
    vec v_half {0.0, 0.0, 0.0}; 
    for (std::size_t i {0};i<3;++i){
        v_half[i] = m_vel[i] + m_acc[i] / 2 * dt;
        m_pos[i] = m_pos[i] + v_half[i] * dt;
        m_vel[i] = v_half[i] + vxb[i] / 2 * dt;
    }
    */

    m_acc = vxb;

    // Log positions for single_ion_path
    if (m_save_trajectory)
        m_pos_log.emplace_back(m_pos);
}

// NOTE: should the output file always be single_ion_path.csv? 
// Think the filename should be an argument maybe with a the default as single_ion_path
void Particle::write_pos_log()
{
    std::ofstream outf { m_log_filename };
    if (!outf) 
    {
        std::cerr << "Error opening single ion position log file\nFilename:\t" 
            << m_log_filename << '\n';
        return;
    }

    for (vec& pos : m_pos_log)
    {
        outf << pos << '\n';
    }
}

bool Particle::inRegion(const Grid::Dimensions& dim)
{
    if (m_pos[0] < 0 || m_pos[0] > dim.X_max){
        return false;
    }
    if (m_pos[1] < 0 || m_pos[1] > dim.Y_max){
        return false;
    }
    if (m_pos[2] < 0 || m_pos[2] > dim.Z_max){
        return false;
    }
    return true;
}

bool Particle::passed(const Grid::Dimensions& dim)
{
    if (m_pos[0] < 0 && m_pos[1] > 0.0 && m_pos[2] > dim.Y_max && m_pos[2] < dim.Z_max)
        return true;
    return false;
}
