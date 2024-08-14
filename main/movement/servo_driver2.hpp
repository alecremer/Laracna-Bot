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
    servo_driver2(){};
    servo_driver2(const servo_channel_t& servo_channel, uint8_t& channel_number, ledc_timer_t ledc_timer_idx = LEDC_TIMER_0);
    float read_servo(const int& servo_idx);
    void move_servo(const int& servo_idx, const float& angle);

};


#endif