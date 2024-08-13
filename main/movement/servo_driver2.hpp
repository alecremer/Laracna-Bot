#ifndef SERVO_DRIVER2_HPP
#define SERVO_DRIVER2_HPP

extern "C" {
    #include "iot_servo.h"
}

class servo_driver2
{

private:
    servo_config_t servo_cfg;
public:
    servo_driver2(gpio_num_t servo_gpios[], ledc_channel_t ledc_ch[], ledc_timer_t ledc_timer_idx = LEDC_TIMER_0);
    float read_servo(const int& servo_idx);
    void move_servo(const int& servo_idx, const float& angle);

};


#endif