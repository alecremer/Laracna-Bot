#ifndef LARACNA_HPP
#define LARACNA_HPP

#include "move_manager.hpp"
#include "cmd_interface.hpp"

class laracna
{

private:


public:
    laracna(const vector<leg_config>& leg_config):move_man(leg_config){};
    void initialize(void);
    move_manager move_man;
    cmd_interface cmd;
};


#endif
