#include <console/console.c>
#include "movement/servo_driver.hpp"
#include <iostream>
#include <string>
#include "data_manager.hpp"
#include "laracna.hpp"

extern "C" {
    #include "esp_console.h"
    #include "argtable3/argtable3.h"
    #include "esp_log.h"
    #include "iot_servo.h"
}
// servo_driver d(14);


static struct {
    struct arg_int *angle;
    struct arg_lit *negative;
    struct arg_end *end;
} servo_move_cmd_args;

// static int servo_move_cmd(int argc, char **argv){
    
//     int nerrors = arg_parse(argc, argv, (void **) &servo_move_cmd_args);
//     if (nerrors != 0) {
//         arg_print_errors(stderr, servo_move_cmd_args.end, argv[0]);
//         return 1;
//     }

//     int angle = servo_move_cmd_args.angle->ival[0];
//     if(servo_move_cmd_args.negative->count > 0) angle = -angle;
//     ESP_LOGI(__func__, "angle: %d", angle);

//     d.Move(angle);
//     return 0;
// }

// void register_servo_move_cmd(void){
    
//     servo_move_cmd_args.angle = arg_int0(NULL, NULL, "<angle>", "ângulo do servo");
//     servo_move_cmd_args.negative = arg_lit0("n", "negative", "n para ângulo negativo");
//     servo_move_cmd_args.end = arg_end(2);
    
//     const esp_console_cmd_t servo_move = {
//         .command = "move",
//         .help = "Move servo to angle",
//         .hint = NULL,
//         .func = &servo_move_cmd,
//         .argtable = &servo_move_cmd_args,
//         .func_w_context = NULL,
//         .context = NULL
//     };
//     ESP_ERROR_CHECK( esp_console_cmd_register(&servo_move) );
// }

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {

    // gpio_num_t g[8];

    // servo_channel_t s{
    //     .servo_pin  {
    //             GPIO_NUM_12,
    //             GPIO_NUM_14,
    //             GPIO_NUM_27,
    //             GPIO_NUM_26,
    //             // GPIO_NUM_25,
    //             // GPIO_NUM_33,
    //             // GPIO_NUM_32,
    //             // GPIO_NUM_15,
    //         },
    //     .ch = {
    //             LEDC_CHANNEL_0,
    //             LEDC_CHANNEL_1,
    //             LEDC_CHANNEL_2,
    //             LEDC_CHANNEL_3,
    //             // LEDC_CHANNEL_4,
    //             // LEDC_CHANNEL_5,
    //             // LEDC_CHANNEL_6,
    //             // LEDC_CHANNEL_7,
    //         }
    // };
    

    // servo_config_t servo_cfg = {
    // .max_angle = 180,
    // .min_width_us = 500,
    // .max_width_us = 2500,
    // .freq = 50,
    // .timer_number = LEDC_TIMER_0,
    // .channels = s,
    //     .channel_number = 4,
    // } ;
    // iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);

    // float angle = 100.0f;

    // // Set angle to 100 degree
    // iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, angle);

    // // Get current angle of servo
    // iot_servo_read_angle(LEDC_LOW_SPEED_MODE, 0, &angle);
    // std::cout << "angle: " << angle;
    // sleep(1);
    // iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, 0);
    // sleep(1);
    // iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, 100);

    // //deinit servo
    // iot_servo_deinit(LEDC_LOW_SPEED_MODE);


    // leg_config config;
    // config.coxa_length = 1;
    // config.femur_length = 1;
    // config.tibia_length = 1;
    // config.coxa_servo_gpio = 12;
    // config.femur_servo_gpio = 14;
    // config.tibia_servo_gpio = 27;
    // config.id = "test";

    // leg_config config2;
    // config.coxa_length = 1;
    // config.femur_length = 1;
    // config.tibia_length = 1;
    // config.coxa_servo_gpio = 26;
    // config.femur_servo_gpio = 25;
    // config.tibia_servo_gpio = 33;
    // config.id = "test_1";

    // leg_config config3;
    // config.coxa_length = 1;
    // config.femur_length = 1;
    // config.tibia_length = 1;
    // config.coxa_servo_gpio = 16;
    // config.femur_servo_gpio = 17;
    // config.tibia_servo_gpio = 5;
    // config.id = "test_2";

    // vector<leg_config> l;
    // l.push_back(config);
    // l.push_back(config2);
    // l.push_back(config3);
    // laracna laracna_instance(l);
    // laracna_instance.initialize();

    laracna lara;
    lara.build_legs();
    // std::cout << "moving" << std::endl;
    // lara.move_man.get_leg("leg_l0").move_servo_coxa(100);
    // sleep(1);
    // lara.move_man.get_leg("leg_l0").move_servo_coxa(50);
    // sleep(1);
    // lara.move_man.get_leg("leg_l0").move_servo_coxa(0);
    lara.initialize();
    // std::cout << b.a;

    /*
        * TODO: Implement Console Destructor
        * TODO: Implement Argument Parser
        * TODO: Create servo_controller command with 4 arguments: x, y, z, leg_idx
        *
    */
//    data_manager data;
//    data.read_config();
//    std::string data_txt = "test write data "; 
//    data.write_config(data_txt);
//    d.Move(45);
//    console_main(register_servo_move_cmd);

}