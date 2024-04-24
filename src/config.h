#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <random>

#include "Random.h"
#include "node.h"
#include "myVectorMath.h"
#include "file_input.h"
#include "grid.h"
#include "particle.h"
#include "methods.h"

#define DT 1E-8

using vec = std::array<double, 3>;

std::ostream& operator<<(std::ostream& out, const vec& a);
std::ofstream& operator<<(std::ofstream& out, const vec& a);
vec operator-(const vec& a, const vec& b);

#endif
