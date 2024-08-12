//
//  Create by Ale - 1/8/23
//


#ifndef SERVO_DRIVER_HPP
#define SERVO_DRIVER_HPP

#include <string>
extern "C" {
#include "driver/mcpwm_prelude.h"
}

class servo_driver {
public:
    servo_driver(int gpio_servo);

    ~servo_driver();

    mcpwm_timer_handle_t timer;

    // The time base of the final PWM signal. It also determines the event timing of other submodules
    mcpwm_timer_config_t timer_config;

    // operator: generate PWM waveform
    mcpwm_oper_handle_t oper;

    mcpwm_operator_config_t operator_config;

    // comparator: compare base time with configured value
    mcpwm_cmpr_handle_t comparator;

    mcpwm_comparator_config_t comparator_config;

    // can generate a pair of PWM waves complementary or independently
    mcpwm_gen_handle_t generator;

    mcpwm_generator_config_t generator_config;

    int32_t getGpio();

    void Move(int angle);

private:
    int32_t internal_gpio_servo;
};

#endif
