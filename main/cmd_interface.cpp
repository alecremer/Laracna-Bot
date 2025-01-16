#include "cmd_interface.hpp"
#include "laracna.hpp"
#include "utils/math_utils.hpp"

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
    struct arg_lit *read;
    struct arg_end *end;
} servo_move_cmd_args;

static struct {
    struct arg_str *cmd;
    struct arg_str *leg_id;
    struct arg_str *data;
    struct arg_end *end;
} leg_cmd_args;


static struct {
    struct arg_str *cmd;
    struct arg_str *data;
    struct arg_end *end;
} data_cmd_args;

static MoveManager m;
static const char* TAG_MOVE_MAN = "DATA> ";
static const char* TAG_LEG_CMD = "LEG_CMD> ";

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


    if(servo_move_cmd_args.read->count > 0){
        leg_move_controller leg_ctrl = m.get_leg(leg);

        ESP_LOGE(__func__, "leg %s angles:", leg_ctrl.id.c_str());
        ESP_LOGE(__func__, "coxa: %f", leg_ctrl.read_servo_angle("c"));
        ESP_LOGE(__func__, "femur: %f", leg_ctrl.read_servo_angle("f"));
        ESP_LOGE(__func__, "tibia: %f", leg_ctrl.read_servo_angle("t"));

    }

    leg_move_controller leg_ctrl = m.get_leg(leg);
    if(leg_ctrl.id.empty() || leg_ctrl.id != leg || leg_ctrl.id == "error"){

        ESP_LOGE(__func__, "leg %s not founded", leg.c_str());

        vector<string> leg_ids = m.get_all_leg_ids();
        string ids_str = "";
        for(string& leg: leg_ids) ids_str = ids_str + leg + ", ";

        ESP_LOGE(__func__, "available legs: %s", ids_str.c_str());
        return 0;

    }
    else{

        if(seg == "c")
            m.get_leg(leg).move_servo_coxa(angle);
        else if(seg == "f")
            m.get_leg(leg).move_servo_femur(angle);
        else if(seg == "t")
            m.get_leg(leg).move_servo_tibia(angle);
        else{
            ESP_LOGE(__func__, "leg segment %s not founded", seg.c_str());
            return 0;

        }
        ESP_LOGI(__func__, "leg: %s", leg.c_str());
        ESP_LOGI(__func__, "angle: %d", angle);
        return 0;

    }

}


int leg_cmd_(void* context, int argc, char **argv){
    
    
    // check args
    int nerrors = arg_parse(argc, argv, (void **) &leg_cmd_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, leg_cmd_args.end, argv[0]);
        return 1;
    }

    string cmd = leg_cmd_args.cmd->sval[0];
    string leg_id = leg_cmd_args.leg_id->sval[0];

    if(cmd == "move"){

        if(leg_cmd_args.data->count == 3){
            float x = stof(leg_cmd_args.data->sval[0]);
            float y = stof(leg_cmd_args.data->sval[1]);
            float z = stof(leg_cmd_args.data->sval[2]);
            
            ESP_LOGI(TAG_LEG_CMD, "Move to  %f, %f, %f", x, y, z);

            array<float, 3> position = {x, y, z};
            m.move_leg_to_position(leg_id, position);
            
            return 1;
        }
        ESP_LOGE(TAG_LEG_CMD, "Invalid number of elements");
        return 0;

    }
    if(cmd == "read"){

        array<float, 3> pos = MathUtils::rad2deg_array(m.get_leg(leg_id).get_pos_from_angles());

        ESP_LOGI(TAG_LEG_CMD, "%s pos: %f, %f, %f", leg_id.c_str(), pos[0], pos[1], pos[2]);
        return 0;

    }
    else{

        ESP_LOGE(TAG_LEG_CMD, "Unknow command %s", cmd.c_str());
    
    }

    return 0;

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
    string key = "";
    
    

    // if(cmd == "r"){
    //     ESP_LOGI("CONFIG> ", "reading config:");
    //     ESP_LOGI("CONFIG> ", "\n%s", data_man_.read_config().c_str());
    // }
    if(cmd == "read"){
        ESP_LOGI(TAG_MOVE_MAN, "\n%s", DataManager::get_instance().read_file(data).c_str());
    }
    else if(cmd == "config"){
        
        if(data_cmd_args.data->count > 1){
            key = data_cmd_args.data->sval[0];
            data = data_cmd_args.data->sval[1];
            ESP_LOGI(TAG_MOVE_MAN, "data: %s", data.c_str());
            ESP_LOGI(TAG_MOVE_MAN, "key: %s", key.c_str());
            ESP_LOGI(TAG_MOVE_MAN, "write config: %s=%s", key.c_str(), data.c_str());
            DataManager::get_instance().write_config(key, data);
        } 
        else{
            
            ESP_LOGE(TAG_MOVE_MAN, "Data or key expected");
        }
    }
    else if(cmd == "list"){
        ESP_LOGI(TAG_MOVE_MAN, "list files:");
        vector<string> files = DataManager::get_instance().list_files();
        for(string s : files){

            ESP_LOGI("->", "%s", s.c_str());
        
        }

    }
    else if(cmd == "del"){
        
        bool success = DataManager::get_instance().delete_file(data);

        if(success) ESP_LOGI(TAG_MOVE_MAN, "File deleted: %s", data.c_str());
        else ESP_LOGE(TAG_MOVE_MAN, "Error deleting file: %s", data.c_str());
    }
    else{
        ESP_LOGI(TAG_MOVE_MAN, "cmd '%s' not founded", cmd.c_str());

    }

    return 0;


}

void CLI::register_servo_move_cmd(void){
    
    ESP_LOGI(__func__, "register");
    
    servo_move_cmd_args.leg_id = arg_str0(NULL, NULL, "<leg_id>", "ID referente á pata");
    servo_move_cmd_args.leg_servo_seg = arg_str0(NULL, NULL, "<leg_segment>", "ID referente ao segmento (c - coxa, f - femur, t - tibia)");
    servo_move_cmd_args.angle = arg_int0(NULL, NULL, "<angle>", "ângulo do servo");
    servo_move_cmd_args.negative = arg_lit0("n", "negative", "n para ângulo negativo");
    servo_move_cmd_args.read = arg_lit0("r", "read", "r para ler angulos");
    servo_move_cmd_args.end = arg_end(2);
    void* ctx = &(move_man);

    const esp_console_cmd_t servo_move = {
        .command = "servo",
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
    
    data_cmd_args.cmd = arg_str1(NULL, NULL, "<cmd>", "read, write, list, config, del");
    data_cmd_args.data = arg_strn(NULL, NULL, "<data>", 0, 2, "passado para write");
    data_cmd_args.end = arg_end(3);

    const esp_console_cmd_t data = {
        .command = "data",
        .help = "gerenciamento de configurações",
        .hint = NULL,
        .func = &data_cmd,
        .argtable = &data_cmd_args,
        .func_w_context = NULL,
        .context = NULL
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&data) );


    
}


void CLI::register_leg_cmd(void){
    
    ESP_LOGI(__func__, "register");
    
    leg_cmd_args.cmd = arg_str1(NULL, NULL, "<cmd>", "move");
    leg_cmd_args.leg_id = arg_str1(NULL, NULL, "<leg id>", "");
    leg_cmd_args.data = arg_strn(NULL, NULL, "<data>", 0, 3, "pos");
    leg_cmd_args.end = arg_end(6);
    void* ctx = &(move_man);


    const esp_console_cmd_t leg_cmd = {
        .command = "leg",
        .help = "comandos das patas",
        .hint = NULL,
        .func = NULL,
        .argtable = &leg_cmd_args,
        .func_w_context = &leg_cmd_,
        .context = &ctx
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&leg_cmd) );


    
}

void CLI::register_cmds(void)
{

    register_servo_move_cmd();
    register_data_cmd();
    register_leg_cmd();

}

void CLI::start_console(void)
{
    m = move_man;
    console_main();
    register_cmds();
}
