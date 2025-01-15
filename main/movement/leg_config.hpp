#ifndef LEG_CONFIG
#define LEG_CONFIG

#include <string>
extern "C" {
    #include "iot_servo.h" // to use gpio_num_t and ledc_channel_t
}

using namespace std;

/// @brief Leg abstraction
class LegConfig
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
    float coxa_angle_offset;
    float femur_angle_offset;
    float tibia_angle_offset;
    string id; // used to access leg by user/robot
};


#endif