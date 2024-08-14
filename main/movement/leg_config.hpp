#ifndef LEG_CONFIG
#define LEG_CONFIG

#include <string>
extern "C" {
    #include "iot_servo.h"
}

using namespace std;


class leg_config
{
public:
    gpio_num_t coxa_servo_gpio;
    gpio_num_t femur_servo_gpio;
    gpio_num_t tibia_servo_gpio;
    ledc_channel_t coxa_ledc_channel;
    ledc_channel_t femur_ledc_channel;
    ledc_channel_t tibia_ledc_channel;
    float coxa_length;
    float femur_length;
    float tibia_length;
    string id;
};


#endif