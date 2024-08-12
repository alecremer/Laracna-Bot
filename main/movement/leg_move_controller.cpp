//
//  Create by Ale - 1/8/23
//

#include "leg_move_controller.hpp"
#include "ik.hpp"
#include "servo_driver.hpp"
#include <array>
#include <functional>


void leg_move_controller::move(std::array<float, 3>& position){

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, link_0_length, link_1_length);

    drive_0.Move(servo_angles.at(0));
    drive_1.Move(servo_angles.at(1));
    drive_2.Move(servo_angles.at(2));

}

void leg_move_controller::move_servo_0(const float &angle){ move_servo_x(drive_0, angle);}
void leg_move_controller::move_servo_1(const float &angle){ move_servo_x(drive_1, angle);}
void leg_move_controller::move_servo_2(const float &angle){ move_servo_x(drive_2, angle);}

void leg_move_controller::move_servo_x(servo_driver &_drive, const float &_angle){

    int angle_int = (int) _angle; 
    _drive.Move(angle_int);

}
