//
//  Create by Ale - 1/8/23
//

#include "leg_move_controller.hpp"
#include "ik.hpp"
#include "servo_driver.hpp"
#include <array>
#include <functional>


void leg_move_controller::move(std::array<float, 3>& position){

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, coxa_length, femur_length);

    servo_coxa.Move(servo_angles.at(0));
    servo_femur.Move(servo_angles.at(1));
    servo_tibia.Move(servo_angles.at(2));

}

void leg_move_controller::move_servo_coxa(const float &angle){ move_servo_x(servo_coxa, angle);}
void leg_move_controller::move_servo_femur(const float &angle){ move_servo_x(servo_femur, angle);}
void leg_move_controller::move_servo_tibia(const float &angle){ move_servo_x(servo_tibia, angle);}

void leg_move_controller::move_servo_x(servo_driver &_drive, const float &_angle){

    int angle_int = (int) _angle; 
    _drive.Move(angle_int);

}
