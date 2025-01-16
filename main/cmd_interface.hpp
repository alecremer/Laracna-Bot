
#include "movement/move_manager.hpp"
#include "data_manager.hpp"

extern "C" {
    #include "esp_console.h"
    #include "argtable3/argtable3.h"
    #include "esp_log.h"
}

#ifndef CMD_INTERFACE_HPP
#define CMD_INTERFACE_HPP

class CLI
{
private:

    void register_servo_move_cmd(void);
    void register_data_cmd(void);
    void register_leg_cmd(void);
    void register_cmds(void);
    int servo_move_cmd(void* context, int argc, char **argv);

    friend Laracna;

public:
    CLI(void){};
    void set_move_man(const MoveManager& _move_man){move_man = _move_man;};
    MoveManager move_man;
    void start_console(void);
};

#endif