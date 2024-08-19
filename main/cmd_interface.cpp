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

static struct {
    struct arg_str *cmd;
    struct arg_str *data;
    struct arg_end *end;
} data_cmd_args;

MoveManager m;
data_manager data_man_;

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


int data_cmd(int argc, char **argv){
    
    // check args
    int nerrors = arg_parse(argc, argv, (void **) &data_cmd_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, data_cmd_args.end, argv[0]);
        return 1;
    }

    string cmd = data_cmd_args.cmd->sval[0];
    string data = data_cmd_args.data->sval[0];

    if(cmd == "r"){
        ESP_LOGI("CONFIG> ", "reading config:");
        ESP_LOGI("CONFIG> ", "\n%s", data_man_.read_config().c_str());
    }
    else if(cmd == "w"){
        ESP_LOGI("CONFIG> ", "write config:");
        data_man_.write_config(data);
    }
    else{
        ESP_LOGI("CONFIG> ", "cmd '%s' not founded", cmd.c_str());

    }

    return 0;


}

void CLI::register_servo_move_cmd(void){
    
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

void CLI::register_data_cmd(void){
    
    ESP_LOGI(__func__, "register");
    
    data_cmd_args.cmd = arg_str0(NULL, NULL, "<cmd>", "read- r, write- w");
    data_cmd_args.data = arg_str0(NULL, NULL, "<data>", "passado para write");
    data_cmd_args.end = arg_end(2);

    const esp_console_cmd_t data = {
        .command = "config",
        .help = "gerenciamento de configurações",
        .hint = NULL,
        .func = &data_cmd,
        .argtable = &data_cmd_args,
        .func_w_context = NULL,
        .context = NULL
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&data) );


    
}

void CLI::register_cmds(void)
{

    register_servo_move_cmd();
    register_data_cmd();

}

void CLI::start_console(void)
{
    m = move_man;
    data_man_ = data_man;
    console_main();
    register_cmds();
}
