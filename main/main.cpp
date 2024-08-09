#include <console.c>
#include "leg/servo_drive.hpp"


// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
    /*
        * TODO: Implement Console Destructor
        * TODO: Implement Argument Parser
        * TODO: Create servo_controller command with 4 arguments: x, y, z, leg_idx
        *
    */
   console_main();

}