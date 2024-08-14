#ifndef LARACNA_HPP
#define LARACNA_HPP

#include "movement/move_manager.hpp"
#include "cmd_interface.hpp"
#include "data_manager.hpp"

class laracna
{

private:


public:
    laracna(void){};
    void initialize(void);
    void build_legs(void);
    
    move_manager move_man;
    cmd_interface cmd;
    data_manager data_man;
};


#endif
