#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "grid.h"
#include "node.h"

#include <vector>
#include <string_view>

Grid::Dimensions read_file_header(std::string_view filename);
std::vector<Node> import_file(std::string_view filename);

#endif
