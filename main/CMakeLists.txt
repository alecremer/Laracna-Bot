idf_component_register(
    SRCS "main.cpp"
    "data_manager.cpp"
    "data_manager.hpp"
    # "ik.hpp"
    # "ik.cpp"
    # "leg_move_controller.hpp"
    # "leg_move_controller.cpp"
    "movement/servo_driver.hpp"
    "movement/servo_driver.cpp"
    "console.c"
    INCLUDE_DIRS "" "."
    REQUIRES console fatfs spiffs
)

spiffs_create_partition_image(storage ../partition FLASH_IN_PROJECT)

# Allow all compiler warnings to be displayed
# and restrict all builds to fail in case of warnings
component_compile_options("-Wall")
component_compile_options("-Wextra")
component_compile_options("-Werror")