#ifndef MY_VECTOR_MATH_H
#define MY_VECTOR_MATH_H

#include <array>

using vec = std::array<double, 3>;

namespace Vec 
{

vec cross(vec& a, vec& b);
double magnitude(vec& a);

}

#endif
