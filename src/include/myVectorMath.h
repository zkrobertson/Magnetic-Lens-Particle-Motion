#ifndef MY_VECTOR_MATH_H
#define MY_VECTOR_MATH_H

#include <array>
#include <iostream>
#include <fstream>

using vec = std::array<double, 3>;

std::ostream& operator<<(std::ostream&, const vec&);
std::ofstream& operator<<(std::ofstream&, const vec&);
vec operator-(const vec&, const vec&);

namespace Vec 
{

vec cross(const vec&, const vec&);
double magnitude(vec);

}

#endif
