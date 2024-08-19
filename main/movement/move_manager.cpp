//
//  Create by Ale - 12/8/24
//

#include "move_manager.hpp"
#include <algorithm>

const char* TAG_SERVO_REG = "ServoRegister";
const char* TAG_SERVO_MOVE = "ServoMove";

extern "C"{
    #include "esp_log.h"
}

leg_move_controller MoveManager::get_leg(string id){


    list<leg_move_controller>::iterator result = std::find_if(legs.begin(), legs.end(), [&id](leg_move_controller l){ return (l.id == id);});
    if(result != legs.end())
        return *result;
    else{
        ESP_LOGE("GET_LEG", "leg %s not founded", id.c_str());
        leg_move_controller err;
        err.id = "error";
        return err;
    }
}