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
    leg_move_controller(const int32_t gpio_servo_coxa, const int32_t gpio_servo_femur, const int32_t gpio_servo_tibia,
                        const float&_coxa_length, const float&_femur_length, const float&_tibia_length)
        : servo_coxa(gpio_servo_coxa), servo_femur(gpio_servo_femur), servo_tibia(gpio_servo_tibia) {

        coxa_length = _coxa_length;
        femur_length = _femur_length;
        tibia_length = _tibia_length;
        
    }

    void move(std::array<float, 3>&position);

    void move_servo_coxa(const float&angle);

    void move_servo_femur(const float&angle);

    void move_servo_tibia(const float&angle);

    
    void move_servo_x(servo_driver&drive, const float&angle);

private:
    ik ik_servo;
    servo_driver servo_coxa, servo_femur, servo_tibia;
    float coxa_length, femur_length, tibia_length;

};


#endif
