#include "servo_driver2.hpp"
extern "C" {
    #include "esp_log.h"
    #include "iot_servo.h"
}
#include <vector>
using namespace std;

#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE        0   // Minimum angle
#define SERVO_MAX_DEGREE        180    // Maximum angle

#define SERVO_PULSE_GPIO             32        // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

servo_driver2::servo_driver2(gpio_num_t gpio_num[], ledc_channel_t ledc_ch[], ledc_timer_t ledc_timer_idx = LEDC_TIMER_0){
    servo_cfg = {
    .max_angle = SERVO_MAX_DEGREE,
    .min_width_us = SERVO_MIN_PULSEWIDTH_US,
    .max_width_us = SERVO_MAX_PULSEWIDTH_US,
    .freq = 50,
    .timer_number = ledc_timer_idx,
    .channels = {
        .servo_pin = *gpio_num,
            .ch = *ledc_ch,
        },
        .channel_number = 8,
    } ;
    iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
}

void servo_driver2::move_servo(const int& servo_idx, const float& angle){
    esp_err_t result = iot_servo_write_angle(LEDC_LOW_SPEED_MODE, servo_idx, angle);
    if(result != ESP_OK){
        ESP_LOGE(TAG, "cant write angle (%s)", esp_err_to_name(result));
        return;
    }
}

float servo_driver2::read_servo(const int& servo_idx){
    
    float angle = 0;
    esp_err_t result = iot_servo_read_angle(LEDC_LOW_SPEED_MODE, servo_idx, &angle);
    if(result != ESP_OK){
        ESP_LOGE(TAG, "cant read angle (%s)", esp_err_to_name(result));
        return;
    }

    return angle;

}