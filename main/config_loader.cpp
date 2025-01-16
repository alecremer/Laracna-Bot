#include "config_loader.hpp"

array<float, 3> ConfigLoader::get_leg_angle_offset_config(){

    float coxa_angle_offset = stof(DataManager::get_instance().read_config_field("coxa_angle_offset"));
    float femur_angle_offset = stof(DataManager::get_instance().read_config_field("femur_angle_offset"));
    float tibia_angle_offset = stof(DataManager::get_instance().read_config_field("tibia_angle_offset"));

    array<float, 3> angles_offset = {coxa_angle_offset, femur_angle_offset, tibia_angle_offset};
    return angles_offset;

}

array<float, 3> ConfigLoader::get_leg_length_config(){

    float coxa_angle_length = stof(DataManager::get_instance().read_config_field("coxa_length"));
    float femur_angle_length = stof(DataManager::get_instance().read_config_field("femur_length"));
    float tibia_angle_length = stof(DataManager::get_instance().read_config_field("tibia_length"));

    array<float, 3> lengths = {coxa_angle_length, femur_angle_length, tibia_angle_length};
    return lengths;

}
