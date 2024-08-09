//
//  Create by Ale - 1/8/23
//

// from https://github.com/espressif/esp-idf/blob/master/examples/peripherals/mcpwm/mcpwm_servo_control/main/mcpwm_servo_control_example_main.c 
// ref: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/mcpwm.html

/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

extern "C" {
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"
}

#include <iostream>

#include "servo_drive.hpp"

using namespace std;


// Please consult the datasheet of your servo before changing the following parameters
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2500  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE        -90   // Minimum angle
#define SERVO_MAX_DEGREE        90    // Maximum angle

#define SERVO_PULSE_GPIO             32        // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms

static const char* TAG = "Debug";
bool debug = true;

static uint32_t example_angle_to_compare_2(int angle) {
    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (
               SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

servo_drive::servo_drive(const int32_t gpio_servo) {
    internal_gpio_servo = gpio_servo;

    if (debug)
        ESP_LOGI(TAG, "Create timer and operator");
    timer_config.group_id = 0;
    timer_config.clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT;
    timer_config.resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ;
    timer_config.period_ticks = SERVO_TIMEBASE_PERIOD;
    timer_config.count_mode = MCPWM_TIMER_COUNT_MODE_UP;
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));


    mcpwm_oper_handle_t _oper = NULL;
    mcpwm_operator_config_t _operator_config = mcpwm_operator_config_t();
    _operator_config.group_id = 0; // operator must be in the same group to the timer

    oper = _oper;
    operator_config = _operator_config;

    operator_config.group_id = 0; // operator must be in the same group to the timer
    ESP_ERROR_CHECK(mcpwm_new_operator(&(operator_config), &(oper)));


    if (debug)
        ESP_LOGI(TAG, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    if (debug)
        ESP_LOGI(TAG, "Create comparator and generator from the operator");
    comparator = NULL;
    comparator_config = mcpwm_comparator_config_t();
    // operator_config = operator_config;
    comparator_config.flags.update_cmp_on_tez = true;

    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &(comparator_config), &(comparator)));

    generator = NULL;
    generator_config = mcpwm_generator_config_t();
    generator_config.gen_gpio_num = internal_gpio_servo;

    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &(generator_config), &(generator)));

    // set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare_2(0)));

    if (debug)
        ESP_LOGI(TAG, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    if (debug)
        ESP_LOGI(TAG, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));
}

void servo_drive::Move(int angle) {
    if (debug)
        ESP_LOGI(TAG, "Moving... %i", angle);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare_2(angle)));
}

int32_t servo_drive::getGpio() { return internal_gpio_servo; }
