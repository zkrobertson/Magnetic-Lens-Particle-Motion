#include "file_input.h"

#include <fstream>
#include <iostream>
#include <sstream>

Grid::Dimensions read_file_header(std::string_view filename)
{
    std::cout << "Opening: " << filename << '\n';
    std::ifstream inf { filename };
    if(!inf)
    {
        std::cerr << "Error openeing file: " << filename << '\n';
        return Grid::Dimensions {0,0,0,0,0,0};
    }

    std::cout << "Reading File...";

    std::string _header {};
    std::getline(inf, _header);
    std::string _format {};
    std::getline(inf, _format);

    std::stringstream num_buffer {};

    std::array<double, 9> dimensions {};
    std::size_t index {0};

    bool write_value {false};
    char last_character {' '};

    for (char& c : _header)
    {
        if (c == '[') write_value = true;
        else if (c == ']') write_value = false;
        else if (write_value){
            if ( (c >= '0' && c <= '9') || c == '.'){
                num_buffer << c;
            }
            else if (c > 'a' && last_character >= '0' && last_character <= '9'){
                num_buffer >> dimensions[index];
                num_buffer.clear();
                ++index;
            }
        }
        if (index == 9){
            break;
        }
        last_character = c;
    }

    double x_step {dimensions[6] * 0.001};
    double y_step {dimensions[7] * 0.001};
    double z_step {dimensions[8] * 0.001};
    double x_max {dimensions[3] * 0.001};
    double y_max {dimensions[4] * 0.001};
    double z_max {dimensions[5] * 0.001};

    inf.close();
    std::cout << filename << " read header and set dimensions. File closed\n";

    return Grid::Dimensions{
        x_step,
        y_step,
        z_step,
        x_max,
        y_max,
        z_max,
    };

}

std::vector<Node> import_file(std::string_view filename)
{
    std::cout << "Opening: " << filename << '\n';
    std::ifstream inf { filename };
    if(!inf)
    {
        std::cerr << "Error openeing file: " << filename << '\n';
        return std::vector<Node> {};
    }

    std::cout << "Reading File... ";

    std::string _header {};
    std::getline(inf, _header);
    std::string _format {};
    std::getline(inf, _format);

    std::string line {};
    std::vector<Node> grid {};

    std::array<double, 6> vals {0,0,0,0,0,0};

    std::stringstream buff {};
    std::size_t index {0};

    while(inf)
    {
        std::getline(inf, line);

        char last_letter {'a'};
        for (const char& c : line)
        {
            if(c == ' ' && last_letter != ' ')
            {
                buff >> vals[index];
                ++index;
                buff.clear();
            }else if (c != ' '){
                buff << c;
            }
            last_letter = c;
        }

        buff >> vals[index];
        buff.clear();
        index=0;

        grid.emplace_back( 
            Node{ 
                {vals[0], vals[1], vals[2]},
                {vals[3], vals[4], vals[5]}
            }
        );

    }

    inf.close();
    std::cout << " grid generated. File closed.\n";

    return grid;
}

