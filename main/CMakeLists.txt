idf_component_register(
    SRCS "main.cpp"
    # "ik.hpp"
    # "ik.cpp"
    # "leg_move_controller.hpp"
    # "leg_move_controller.cpp"
    "servo_driver.hpp"
    "servo_driver.cpp"
    "console.c"
    INCLUDE_DIRS "" "." "./leg"
    REQUIRES console fatfs
)

# Allow all compiler warnings to be displayed
# and restrict all builds to fail in case of warnings
component_compile_options("-Wall")
component_compile_options("-Wextra")
component_compile_options("-Werror")