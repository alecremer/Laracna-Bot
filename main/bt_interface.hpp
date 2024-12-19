#include "movement/move_manager.hpp"
#include "data_manager.hpp"

#include <Arduino.h>
#include <BluetoothSerial.h> // Biblioteca para comunicação Bluetooth

#ifndef BT_INTERFACE_HPP
#define BT_INTERFACE_HPP

extern "C" {
    #include "esp_log.h"
}

class BTInterface
{
private:

    void register_servo_move_cmd(void);
    void register_data_cmd(void);
    void register_cmds_on_start(void);
    // int servo_move_cmd(void* context, int argc, char **argv);

public:
    BTInterface(void){};
    void start_console(void);
    MoveManager move_man;
    data_manager data_man;
    void set_data_manager(const data_manager& _data_man){data_man = _data_man;};
    void set_move_man(const MoveManager& _move_man){move_man = _move_man;};
};



#endif