#ifndef MY_VECTOR_MATH_H
#define MY_VECTOR_MATH_H

#include <array>

namespace Vec 
{

std::array<double, 3> cross(std::array<double, 3>& a, std::array<double, 3>& b);
double magnitude(std::array<double, 3> vec);

}

#endif
