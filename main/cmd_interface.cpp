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
    struct arg_str *leg_servo_seg;
    struct arg_int *angle;
    struct arg_lit *negative;
    struct arg_end *end;
} servo_move_cmd_args;

move_manager m;

int servo_move_(void* context, int argc, char **argv){
    
    // check args
    int nerrors = arg_parse(argc, argv, (void **) &servo_move_cmd_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, servo_move_cmd_args.end, argv[0]);
        return 1;
    }

    int angle = servo_move_cmd_args.angle->ival[0];
    if(servo_move_cmd_args.negative->count > 0) angle = -angle;
    
    string leg = servo_move_cmd_args.leg_id->sval[0];
    string seg = servo_move_cmd_args.leg_servo_seg->sval[0];

    leg_move_controller leg_ctrl = m.get_leg(leg);
    if(leg_ctrl.id.empty() || leg_ctrl.id != leg || leg_ctrl.id == "error"){

        ESP_LOGE(__func__, "leg %s not founded", leg.c_str());
        return 0;

    }
    else{
        std::cout << "leg_id: " << leg_ctrl.id << std::endl;

        if(seg == "c")
            m.get_leg(leg).move_servo_coxa(angle);
        else if(seg == "f")
            m.get_leg(leg).move_servo_femur(angle);
        else if(seg == "t")
            m.get_leg(leg).move_servo_femur(angle);
        else{
            ESP_LOGE(__func__, "leg segment %s not founded", seg.c_str());
            return 0;

        }
        ESP_LOGI(__func__, "leg: %s", leg.c_str());
        ESP_LOGI(__func__, "angle: %d", angle);
        return 0;

    }

}

void cmd_interface::register_servo_move_cmd(void){
    
    ESP_LOGI(__func__, "register");
    
    servo_move_cmd_args.leg_id = arg_str0(NULL, NULL, "<leg_id>", "ID referente á pata");
    servo_move_cmd_args.leg_servo_seg = arg_str0(NULL, NULL, "<leg_segment>", "ID referente ao segmento (c - coxa, f - femur, t - tibia)");
    servo_move_cmd_args.angle = arg_int0(NULL, NULL, "<angle>", "ângulo do servo");
    servo_move_cmd_args.negative = arg_lit0("n", "negative", "n para ângulo negativo");
    servo_move_cmd_args.end = arg_end(2);
    void* ctx = &(move_man);

    const esp_console_cmd_t servo_move = {
        .command = "move",
        .help = "Move servo to angle",
        .hint = NULL,
        .func = NULL,
        .argtable = &servo_move_cmd_args,
        .func_w_context = &servo_move_,
        .context = &ctx
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&servo_move) );


    
}

void cmd_interface::register_cmds(void)
{

    register_servo_move_cmd();

}

void cmd_interface::start_console(void)
{
    m = move_man;
    console_main();
    register_cmds();
}
