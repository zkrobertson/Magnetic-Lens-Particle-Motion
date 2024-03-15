#include "config.h"

std::ostream& operator<<(std::ostream& out, const vec& a)
{
    out << a[0] << ',' << a[1] << ',' << a[2];
    return out;
}

std::ofstream& operator<<(std::ofstream& out, const vec& a)
{
    out << a[0] << ',' << a[1] << ',' << a[2];
    return out;
}

vec operator-(const vec& a, const vec& b)
{
    return { a[0]-b[0], a[1]-b[1], a[2]-b[2] };
}

namespace Vec 
{

vec cross(std::array<double, 3>& a, std::array<double, 3>& b)
{
    return { a[1]*b[2]-a[2]*b[1], -a[0]*b[2]+a[2]*b[0], a[0]*b[1]-a[1]*b[0] };
}

double magnitude(vec a)
{
    return sqrt(pow(a[0],2) + pow(a[1],2) + pow(a[2],2));
}

}
