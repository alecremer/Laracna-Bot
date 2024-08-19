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


/// @brief Provides access to legs and control legs gaits
class MoveManager
{
private:
    list<leg_move_controller> legs;

public:
    MoveManager(void){};
    void set_legs(const list<leg_move_controller>& _legs){legs = _legs;};
    leg_move_controller get_leg(string id);

};

#endif