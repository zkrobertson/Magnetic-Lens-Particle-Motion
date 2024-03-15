#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "node.h"
#include "grid.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string_view>
#include <sstream>

Grid::Dimensions read_file_header(std::string_view filename);
std::vector<Node> import_file(std::string_view filename);

#endif
