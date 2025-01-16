#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <array>
#include "data_manager.hpp"

using namespace std;

class ConfigLoader{

private:

public:

    array<float, 3> get_leg_angle_offset_config();
    array<float, 3> get_leg_length_config();


};

#endif // CONFIG_LOADER_HPP