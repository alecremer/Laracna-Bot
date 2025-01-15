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

vector<string> MoveManager::get_all_leg_ids(){
  
  vector<string> leg_ids;
  for(leg_move_controller& leg : legs) leg_ids.push_back(leg.id);
  return leg_ids;

} 

const list<leg_move_controller>& MoveManager::get_all_legs(){ return legs;}

void MoveManager::move_leg_to_position(const string& leg_id, std::array<float, 3>& position){
    get_leg(leg_id).move_to_position(position);
}
