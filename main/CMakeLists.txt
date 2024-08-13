idf_component_register(
    SRCS "main.cpp"
    "data_manager.cpp"
    "data_manager.hpp"
    "move_manager.cpp"
    "move_manager.hpp"
    "laracna.hpp"
    "laracna.cpp"
    # "laracna.cpp"
    # "ik.hpp"
    # "ik.cpp"
    # "leg_move_controller.hpp"
    # "leg_move_controller.cpp"
    "movement/servo_driver.hpp"
    "movement/servo_driver.cpp"
    "console/console.c"
    "cmd_interface.hpp"
    "cmd_interface.cpp"
    "include/iot_servo.c"
    "include/iot_servo.h"
    INCLUDE_DIRS "" "." include
    REQUIRES console fatfs spiffs driver
)

spiffs_create_partition_image(storage ../partition FLASH_IN_PROJECT)

# Allow all compiler warnings to be displayed
# and restrict all builds to fail in case of warnings
component_compile_options("-Wall")
component_compile_options("-Wextra")
component_compile_options("-Werror")