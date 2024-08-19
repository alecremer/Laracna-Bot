//
//  Create by Ale - 1/8/23
//

#include "leg_move_controller.hpp"
#include "ik.hpp"
#include "servo_driver.hpp"


leg_move_controller::leg_move_controller(const LegConfig& leg_config_ext){
    _leg_config = leg_config_ext;
    id = _leg_config.id;
}


void leg_move_controller::move_to_position(std::array<float, 3>& position){

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, coxa_length, femur_length, tibia_length);

    move_servo_coxa(servo_angles.at(0));
    move_servo_femur(servo_angles.at(1));
    move_servo_tibia(servo_angles.at(2));

}

void leg_move_controller::move_servo_coxa(const float &angle){ _servo_driver.move_servo(_leg_config.coxa_ledc_channel, angle);}
void leg_move_controller::move_servo_femur(const float &angle){ _servo_driver.move_servo(_leg_config.femur_ledc_channel, angle);}
void leg_move_controller::move_servo_tibia(const float &angle){ _servo_driver.move_servo(_leg_config.tibia_ledc_channel, angle);}

void leg_move_controller::move_servo_x(servo_driver &_drive, const float &_angle){

    int angle_int = (int) _angle; 
    _drive.Move(angle_int);

}
