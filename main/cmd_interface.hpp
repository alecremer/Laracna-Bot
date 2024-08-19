
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
    void register_cmds(void);
    int servo_move_cmd(void* context, int argc, char **argv);

public:
    CLI(void){};
    void set_move_man(const MoveManager& _move_man){move_man = _move_man;};
    void set_data_manager(const data_manager& _data_man){data_man = _data_man;};
    MoveManager move_man;
    data_manager data_man;
    void start_console(void);
};

#endif