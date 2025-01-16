// #include "movement/move_manager.hpp"
// #include "data_manager.hpp"

// // #include <Arduino.h>
// // #include <BluetoothSerial.h> // Biblioteca para comunicação Bluetooth

// #ifndef BT_INTERFACE_HPP
// #define BT_INTERFACE_HPP

// extern "C" {
//     #include "esp_log.h"
// }

// typedef int (*bt_cmd_func_t)(int argc, char **argv);
// typedef int (*bt_cmd_func_with_context_t)(void *context, int argc, char **argv);

// /**
//  * @brief Bluetooth command description
//  */
// typedef struct {
//     /**
//      * Command name. Must not be NULL, must not contain spaces.
//      * The pointer must be valid until the call to esp_console_deinit.
//      */
//     const char *command;
//     /**
//      * Help text for the command, shown by help command.
//      * If set, the pointer must be valid until the call to esp_console_deinit.
//      * If not set, the command will not be listed in 'help' output.
//      */
//     const char *help;
//     /**
//      * Hint text, usually lists possible arguments.
//      * If set to NULL, and 'argtable' field is non-NULL, hint will be generated
//      * automatically
//      */
//     const char *hint;
//     /**
//      * Pointer to a function which implements the command.
//      * @note: Setting both \c func and \c func_w_context is not allowed.
//      */
//     bt_cmd_func_t func;
//     /**
//      * Array or structure of pointers to arg_xxx structures, may be NULL.
//      * Used to generate hint text if 'hint' is set to NULL.
//      * Array/structure which this field points to must end with an arg_end.
//      * Only used for the duration of esp_console_cmd_register call.
//      */
//     void *argtable;
//     /**
//      * Pointer to a context aware function which implements the command.
//      * @note: Setting both \c func and \c func_w_context is not allowed.
//      */
//     bt_cmd_func_with_context_t func_w_context;
//     /**
//      * Context pointer to user-defined per-command context data.
//      * This is used if context aware function \c func_w_context is set.
//      */
//     void *context;
// } bt_cmd_t;

// class BTInterface
// {
// private:

//     void register_servo_move_cmd(void);
//     void register_data_cmd(void);
//     void register_cmds_on_start(void);
//     // int servo_move_cmd(void* context, int argc, char **argv);

// public:
//     BTInterface(void){};
//     void start_console(void);
//     MoveManager move_man;
//     DataManager data_man;
//     void set_DataManager(const DataManager& _data_man){data_man = _data_man;};
//     void set_move_man(const MoveManager& _move_man){move_man = _move_man;};
// };



// #endif