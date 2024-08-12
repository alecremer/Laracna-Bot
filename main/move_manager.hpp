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

struct leg_config
{
    int coxa_servo_gpio;
    int femur_servo_gpio;
    int tibia_servo_gpio;
    float coxa_length;
    float femur_length;
    float tibia_length;
    string id;
};


class move_manager
{
private:

public:

    list<leg_move_controller> legs;
    move_manager(const vector<leg_config>& leg_configs);

};

#endif