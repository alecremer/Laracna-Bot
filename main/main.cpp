#include <console/console.c>
#include "movement/servo_driver.hpp"
#include <iostream>
#include <string.h>
#include "data_manager.hpp"
#include "laracna.hpp"

extern "C" {
    #include "esp_console.h"
    #include "argtable3/argtable3.h"
    #include "esp_log.h"
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

    leg_config config;
    config.coxa_length = 1;
    config.femur_length = 1;
    config.tibia_length = 1;
    config.coxa_servo_gpio = 14;
    config.femur_servo_gpio = 15;
    config.tibia_servo_gpio = 16;
    config.id = "test";

    vector<leg_config> l;
    l.push_back(config);
    laracna laracna_instance(l);
    laracna_instance.initialize();

    
    // std::cout << b.a;

    /*
        * TODO: Implement Console Destructor
        * TODO: Implement Argument Parser
        * TODO: Create servo_controller command with 4 arguments: x, y, z, leg_idx
        *
    */
   data_manager data;
//    d.Move(45);
//    console_main(register_servo_move_cmd);

}