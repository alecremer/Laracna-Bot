//
//  Create by Ale - 1/8/23
//

#ifndef LEG_MOVE_CONTROLLER_HPP
#define LEG_MOVE_CONTROLLER_HPP


#include <array>
#include <iostream>

#include "ik.hpp"
#include "servo_driver.hpp"
#include "servo_driver2.hpp"
#include "movement/leg_config.hpp"

class leg_move_controller {
public:
    leg_move_controller(const leg_config& leg_config_ext);
    // leg_move_controller(const int32_t gpio_servo_coxa, const int32_t gpio_servo_femur, const int32_t gpio_servo_tibia,
    //                     const float&_coxa_length, const float&_femur_length, const float&_tibia_length)
    //     : servo_coxa(gpio_servo_coxa), servo_femur(gpio_servo_femur, servo_coxa.timer), servo_tibia(gpio_servo_tibia, servo_coxa.timer) {

    //     coxa_length = _coxa_length;
    //     femur_length = _femur_length;
    //     tibia_length = _tibia_length;

    //     timer = servo_coxa.timer;
    //     servo_coxa.start_timer();
        
    // }
    // leg_move_controller(const int32_t gpio_servo_coxa, const int32_t gpio_servo_femur, const int32_t gpio_servo_tibia,
    //                     const float&_coxa_length, const float&_femur_length, const float&_tibia_length, mcpwm_timer_handle_t timer_ext)
    //     : servo_coxa(gpio_servo_coxa, timer_ext), servo_femur(gpio_servo_femur, timer_ext), servo_tibia(gpio_servo_tibia, timer_ext) {

    //     coxa_length = _coxa_length;
    //     femur_length = _femur_length;
    //     tibia_length = _tibia_length;

    //     timer = servo_coxa.timer;
    //     servo_coxa.start_timer();
        
    // }
    std::string id = "";

    void move_to_position(std::array<float, 3>&position);

    void move_servo_coxa(const float&angle);

    void move_servo_femur(const float&angle);

    void move_servo_tibia(const float&angle);

    void set_driver(const servo_driver2& _driver){_servo_driver = _driver;};
    mcpwm_timer_handle_t timer;

    

private:
    ik ik_servo;
    servo_driver2 _servo_driver;
    float coxa_length, femur_length, tibia_length;
    leg_config _leg_config;
    void move_servo_x(servo_driver&drive, const float&angle);

};


#endif
