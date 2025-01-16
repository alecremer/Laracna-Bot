//
//  Create by Ale - 1/8/23
//
#include "config.hpp"

#include "leg_move_controller.hpp"
#include "utils/math_utils.hpp"
#include "ik.hpp"
#include "servo_driver.hpp"
#include "data_manager.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <array>
// #define CALIB_MOVE

extern "C"{

#include "esp_log.h"

}

using namespace std;

leg_move_controller::leg_move_controller(const LegConfig& leg_config_ext){
    _leg_config = leg_config_ext;
    id = _leg_config.id;

    
}


void leg_move_controller::move_to_position(std::array<float, 3>& position){

#ifdef CALIB_MOVE

        _leg_config.coxa_angle_offset = stof(DataManager::get_instance().read_config_field("coxa_angle_offset"));
        _leg_config.femur_angle_offset = stof(DataManager::get_instance().read_config_field("femur_angle_offset"));
        _leg_config.tibia_angle_offset = stof(DataManager::get_instance().read_config_field("tibia_angle_offset"));

        _leg_config.coxa_length = std::stof(DataManager::get_instance().read_config_field("coxa_length"));
        _leg_config.femur_length = std::stof(DataManager::get_instance().read_config_field("femur_length"));
        _leg_config.tibia_length = std::stof(DataManager::get_instance().read_config_field("tibia_length"));

#endif

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, _leg_config.coxa_length, _leg_config.femur_length, _leg_config.tibia_length);



    float coxa_angle = servo_angles.at(0) + MathUtils::degToRad(_leg_config.coxa_angle_offset);
    float femur_angle = servo_angles.at(1) + MathUtils::degToRad(_leg_config.femur_angle_offset);
    float tibia_angle = servo_angles.at(2) + MathUtils::degToRad(_leg_config.tibia_angle_offset);

    coxa_angle = MathUtils::simplify_angle_rad(coxa_angle);
    femur_angle = MathUtils::simplify_angle_rad(femur_angle);
    tibia_angle = MathUtils::simplify_angle_rad(tibia_angle);
    
    
    bool coxa_angle_ok = (0 <= coxa_angle && coxa_angle <= M_PI);
    bool femur_angle_ok = (0 <= femur_angle && femur_angle <= M_PI);
    bool tibia_angle_ok = (0 <= tibia_angle && tibia_angle <= M_PI);
    
    if(coxa_angle_ok && femur_angle_ok && tibia_angle_ok){

        move_servo_coxa(MathUtils::radToDeg(coxa_angle));
        move_servo_femur(MathUtils::radToDeg(femur_angle));
        move_servo_tibia(MathUtils::radToDeg(tibia_angle));
        ESP_LOGI("IK> ", "Moving -> coxa: %f \nfemur: %f \ntibia: %f\n", MathUtils::radToDeg(coxa_angle), MathUtils::radToDeg(femur_angle), MathUtils::radToDeg(tibia_angle));
        ESP_LOGI("IK> ", "Before -> coxa: %f \nfemur: %f \ntibia: %f\n", MathUtils::radToDeg(servo_angles.at(0)), MathUtils::radToDeg(servo_angles.at(1)), MathUtils::radToDeg(servo_angles.at(2)));
    }
    else{
        ESP_LOGE("IK> ", "Invalid position, \nangles: \ncoxa: %f\n femur: %f\n tibia: %f", MathUtils::radToDeg(coxa_angle), MathUtils::radToDeg(femur_angle), MathUtils::radToDeg(tibia_angle));
    }

}

void leg_move_controller::move_servo_coxa(const float &angle){ _servo_driver.move_servo(_leg_config.coxa_ledc_channel, angle);}
void leg_move_controller::move_servo_femur(const float &angle){ _servo_driver.move_servo(_leg_config.femur_ledc_channel, angle);}
void leg_move_controller::move_servo_tibia(const float &angle){ _servo_driver.move_servo(_leg_config.tibia_ledc_channel, angle);}

void leg_move_controller::move_servo_x(servo_driver &_drive, const float &_angle){

    int angle_int = (int) _angle; 
    _drive.Move(angle_int);

}


array<float, 3> leg_move_controller::get_pos_from_angles(){

#ifdef CALIB_MOVE

    _leg_config.coxa_angle_offset = stof(DataManager::get_instance().read_config_field("coxa_angle_offset"));
    _leg_config.femur_angle_offset = stof(DataManager::get_instance().read_config_field("femur_angle_offset"));
    _leg_config.tibia_angle_offset = stof(DataManager::get_instance().read_config_field("tibia_angle_offset"));

    _leg_config.coxa_length = std::stof(DataManager::get_instance().read_config_field("coxa_length"));
    _leg_config.femur_length = std::stof(DataManager::get_instance().read_config_field("femur_length"));
    _leg_config.tibia_length = std::stof(DataManager::get_instance().read_config_field("tibia_length"));

    DataManager::get_instance().write_file(to_string(_leg_config.coxa_length) + "\n", "c");
    DataManager::get_instance().write_file(to_string(_leg_config.femur_length) + "\n", "c");
    DataManager::get_instance().write_file(to_string(_leg_config.tibia_length) + "\n\n\n", "c");

#endif


    array<float, 3> angles_d{read_servo_angle("c"), read_servo_angle("f"), read_servo_angle("t")};
    array<float, 3> angles = MathUtils::deg2rad_array(angles_d);
    array<float, 3> pos;
    
    float xy_footprint = _leg_config.coxa_length + _leg_config.femur_length*cos(angles[1] + MathUtils::degToRad(_leg_config.femur_angle_offset)) + _leg_config.tibia_length*cos(angles[2] + MathUtils::degToRad(_leg_config.tibia_angle_offset));
    
    pos[0] = xy_footprint * cos(angles[0] + MathUtils::degToRad(_leg_config.coxa_angle_offset));
    pos[1] = xy_footprint * sin(angles[0] + MathUtils::degToRad(_leg_config.coxa_angle_offset));
    pos[2] = _leg_config.femur_length * sin(angles[1] + MathUtils::degToRad(_leg_config.femur_angle_offset)) - _leg_config.tibia_length * sin(angles[2] + MathUtils::degToRad(_leg_config.tibia_angle_offset));

    return pos;
}

float leg_move_controller::read_servo_angle(const string& servo_id){
    
    // select servo
    int servo_idx = _leg_config.coxa_ledc_channel; // default coxa == 'c'
    if(servo_id == "f") servo_idx = _leg_config.femur_ledc_channel;
    else if(servo_id == "t") servo_idx = _leg_config.tibia_ledc_channel;

    return _servo_driver.read_servo(servo_idx);

}

