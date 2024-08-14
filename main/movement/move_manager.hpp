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


class move_manager
{
private:
    list<leg_move_controller> legs;

public:
    move_manager(void){};
    void set_legs(const list<leg_move_controller>& _legs){legs = _legs;};
    leg_move_controller get_leg(string id);

};

#endif