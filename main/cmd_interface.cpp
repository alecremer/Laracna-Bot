#include "cmd_interface.hpp"
#include "laracna.hpp"

extern "C" {
    #include "esp_console.h"
    #include "argtable3/argtable3.h"
    #include "esp_log.h"
    #include "console/console.c"
}

#include <functional>

static struct {
    struct arg_str *leg_id;
    struct arg_int *angle;
    struct arg_lit *negative;
    struct arg_end *end;
} servo_move_cmd_args;


int servo_move_(void* context, int argc, char **argv){
    
    // check args
    int nerrors = arg_parse(argc, argv, (void **) &servo_move_cmd_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, servo_move_cmd_args.end, argv[0]);
        return 1;
    }

    int angle = servo_move_cmd_args.angle->ival[0];
    if(servo_move_cmd_args.negative->count > 0) angle = -angle;
    ESP_LOGI(__func__, "angle: %d", angle);

    // _laracna.
    // d.Move(angle);
    return 0;
}

void cmd_interface::register_servo_move_cmd(void){
    
    servo_move_cmd_args.angle = arg_int0(NULL, NULL, "<angle>", "ângulo do servo");
    servo_move_cmd_args.negative = arg_lit0("n", "negative", "n para ângulo negativo");
    servo_move_cmd_args.end = arg_end(2);
    // auto cont = this;
    // const esp_console_cmd_t servo_move = {
    //     .command = "move",
    //     .help = "Move servo to angle",
    //     .hint = NULL,
    //     // .func = NULL,
    //     .argtable = &servo_move_cmd_args,
    //     .func_w_context = &servo_move_,
    //     .context = cont
    // };
    // ESP_ERROR_CHECK( esp_console_cmd_register(&servo_move) );


    
}

void cmd_interface::register_cmds(void)
{

    register_servo_move_cmd();

}

void cmd_interface::start_console(void)
{
    // std::function<void(void)> f = [&](){this->register_cmds();};
    console_main();
    this->register_cmds();
    // console_start();
}
