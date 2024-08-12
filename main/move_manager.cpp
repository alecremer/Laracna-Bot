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

move_manager::move_manager(const vector<leg_config>& leg_configs){

    // populate legs
    for(int i=0; i<leg_configs.size(); i++){
        leg_move_controller leg{
            leg_configs[i].coxa_servo_gpio,
            leg_configs[i].femur_servo_gpio,
            leg_configs[i].tibia_servo_gpio,
            leg_configs[i].coxa_length,
            leg_configs[i].femur_length,
            leg_configs[i].tibia_length
        };
        leg.id = leg_configs[i].id;     
        legs.push_back(leg);
    }
}