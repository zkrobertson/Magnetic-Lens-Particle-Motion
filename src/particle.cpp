#include "config.h"

Particle::Particle (
    std::array<double, 3> pos,
    std::array<double, 3> vel,
    std::array<double, 3> acc,
    double mass
) : m_pos { pos }
    , m_vel { vel }
    , m_acc { acc }
    , m_mass { mass }
{ m_pos_log.emplace_back(m_pos); }

vec Particle::pos() { return m_pos; }
vec Particle::vel() { return m_vel; }
vec Particle::acc() { return m_acc; }
double Particle::mass() { return m_mass; }

void Particle::print()
{
    std::cout << "Mass: " << m_mass << " \n"
        << "Pos: " << m_pos << '\n'
        << "Vel: " << m_vel << '\n'
        << "Acc: " << m_acc << '\n';
}

// Leap-Frog Integration
bool Particle::updatePos(vec B, const bool save_trajectory)
{
    vec vxb = Vec::cross(m_vel, B);

    for (std::size_t i {0};i<3;++i){
        m_pos[i] = m_pos[i] + m_vel[i] * DT + 0.5 * m_acc[i] * DT * DT;
        vxb[i] = vxb[i] * 1.602E-19 / m_mass;
        m_vel[i] = m_vel[i] + (vxb[i] + m_acc[i])/2 * DT;
    }

    m_acc = vxb;

    // Log positions for single_ion_path
    if (save_trajectory)
        m_pos_log.emplace_back(m_pos);

    return inRegion();
}

void Particle::write_pos_log()
{
    std::ofstream outf { "single_ion_path.csv" };
    for (vec& pos : m_pos_log)
    {
        outf << pos << '\n';
    }
}

bool Particle::inRegion()
{
    if (m_pos[0] < 0 || m_pos[0] > 0.115){
        return false;
    }
    if (m_pos[1] < 0 || m_pos[1] > 0.0254){
        return false;
    }
    if (m_pos[2] < 0 || m_pos[2] > 0.150){
        return false;
    }
    return true;
}
