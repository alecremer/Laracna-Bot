//
//  Create by Ale - 12/8/24
//


#include "movement/leg_move_controller.hpp"
#include <string>
#include <list>
#include <vector>

#ifndef MOVE_MANAGER_HPP
#define MOVE_MANAGER_HPP

using namespace std;

class leg_config
{
public:
    gpio_num_t coxa_servo_gpio;
    gpio_num_t femur_servo_gpio;
    gpio_num_t tibia_servo_gpio;
    float coxa_length;
    float femur_length;
    float tibia_length;
    string id;
};


class move_manager
{
private:
    list<leg_move_controller> legs;

public:

    move_manager(const vector<leg_config>& leg_configs);
    leg_move_controller get_leg(string id);

};

#endif