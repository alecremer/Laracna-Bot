//
//  Create by Ale - 1/8/23
//

#include "leg_move_controller.hpp"
#include "ik.hpp"
#include "servo_driver.hpp"
#include "data_manager.hpp"
#include <iostream>
#include <string>
#include <sstream>

extern "C"{

#include "esp_log.h"

}

leg_move_controller::leg_move_controller(const LegConfig& leg_config_ext){
    _leg_config = leg_config_ext;
    id = _leg_config.id;

    
}


void leg_move_controller::move_to_position(std::array<float, 3>& position){

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, _leg_config.coxa_length, _leg_config.femur_length, _leg_config.tibia_length);

    int coxa_angle = servo_angles.at(0) + _leg_config.coxa_angle_offset;
    int femur_angle = servo_angles.at(1) + _leg_config.femur_angle_offset;
    int tibia_angle = servo_angles.at(2) + _leg_config.tibia_angle_offset;
    
    bool coxa_angle_ok = (0 <= coxa_angle && coxa_angle <= 180);
    bool femur_angle_ok = (0 <= femur_angle && femur_angle <= 180);
    bool tibia_angle_ok = (0 <= tibia_angle && tibia_angle <= 180);
    
    if(coxa_angle_ok && femur_angle_ok && tibia_angle_ok){

        move_servo_coxa(coxa_angle);
        move_servo_femur(femur_angle);
        move_servo_tibia(tibia_angle);
        ESP_LOGI("IK> ", "Moving -> coxa: %i \nfemur: %i \ntibia: %i\n", coxa_angle, femur_angle, tibia_angle);
    }
    else{
        ESP_LOGE("IK> ", "Invalid position, \nangles: \ncoxa: %i\n femur: %i\n tibia: %i", coxa_angle, femur_angle, tibia_angle);
    }

}

void leg_move_controller::move_servo_coxa(const float &angle){ _servo_driver.move_servo(_leg_config.coxa_ledc_channel, angle);}
void leg_move_controller::move_servo_femur(const float &angle){ _servo_driver.move_servo(_leg_config.femur_ledc_channel, angle);}
void leg_move_controller::move_servo_tibia(const float &angle){ _servo_driver.move_servo(_leg_config.tibia_ledc_channel, angle);}

void leg_move_controller::move_servo_x(servo_driver &_drive, const float &_angle){

    int angle_int = (int) _angle; 
    _drive.Move(angle_int);

}

int leg_move_controller::read_servo_angle(const string& servo_id){
    
    // select servo
    int servo_idx = _leg_config.coxa_ledc_channel; // default coxa == 'c'
    if(servo_id == "f") servo_idx = _leg_config.femur_ledc_channel;
    else if(servo_id == "t") servo_idx = _leg_config.tibia_ledc_channel;

    return _servo_driver.read_servo(servo_idx);

}

