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


// move_manager::move_manager(){

//     int leg_count = leg_configs.size();

//     if(leg_count == 0) ESP_LOGE(TAG_SERVO_REG, "leg configuration vector empty");

//     // leg_move_controller leg;
//     // leg.move_servo_coxa = 


//     // leg_move_controller leg_ref{
//     //     leg_configs[0].coxa_servo_gpio,
//     //     leg_configs[0].femur_servo_gpio,
//     //     leg_configs[0].tibia_servo_gpio,
//     //     leg_configs[0].coxa_length,
//     //     leg_configs[0].femur_length,
//     //     leg_configs[0].tibia_length
//     // };

//     // if(leg_count > 1){

//     //     // populate legs
//     //     for(int i=1; i<leg_configs.size(); i++){
//     //         leg_move_controller leg{
//     //             leg_configs[i].coxa_servo_gpio,
//     //             leg_configs[i].femur_servo_gpio,
//     //             leg_configs[i].tibia_servo_gpio,
//     //             leg_configs[i].coxa_length,
//     //             leg_configs[i].femur_length,
//     //             leg_configs[i].tibia_length,
//     //             leg_ref.timer
//     //         };
//     //         leg.id = leg_configs[i].id;     
//     //         legs.push_back(leg);
//     //     }
//     // }

// }

leg_move_controller move_manager::get_leg(string id){

    list<leg_move_controller>::iterator result = std::find_if(legs.begin(), legs.end(), [&id](leg_move_controller l){return (l.id == id);});
    return *result;
}