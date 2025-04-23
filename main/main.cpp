#include "laracna.hpp"

extern "C" void app_main(void) {


    Laracna laracna;
    laracna.build();
    laracna.initialize();
    
}

 /*
#include "bt_interface.hpp"

int Text_Interface() {

    BTInterface terminal_test;

    std::string terminal_command = "move leg0 coxa 45 -n";
    terminal_test.Run_cmd(terminal_command);

    terminal_command = "cmd teste de comando";
    terminal_test.Run_cmd(terminal_command);

    

    return 0;
}

extern "C" void app_main(void) {

    Text_Interface();
    
}*/
