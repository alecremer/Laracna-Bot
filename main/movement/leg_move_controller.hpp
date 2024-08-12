//
//  Create by Ale - 1/8/23
//

#ifndef SERVO_CONTROLLER_HPP
#define SERVO_CONTROLLER_HPP


#include <array>
#include <iostream>

#include "ik.hpp"
#include "servo_driver.hpp"

class leg_move_controller {
public:
    leg_move_controller(const int32_t gpio_servo_0, const int32_t gpio_servo_1, const int32_t gpio_servo_2,
                        const float&_link_0_length, const float&_link_1_length)
        : drive_0(gpio_servo_0), drive_1(gpio_servo_1), drive_2(gpio_servo_2) {
        link_0_length = _link_0_length;
        link_1_length = _link_1_length;
    }

    void move(std::array<float, 3>&position);

    void move_servo_0(const float&angle);

    void move_servo_1(const float&angle);

    void move_servo_2(const float&angle);

    
    void move_servo_x(servo_driver&_drive, const float&_angle);

private:
    ik ik_servo;
    servo_driver drive_0, drive_1, drive_2;
    float link_0_length, link_1_length;

};


#endif
