idf_component_register(
    SRCS "main.cpp"
    "leg/ik.hpp"
    "leg/ik.cpp"
    "leg/leg_move_controller.hpp"
    "leg/leg_move_controller.cpp"
    "leg/servo_drive.hpp"
    "leg/servo_drive.cpp"
    "console.c"
    INCLUDE_DIRS "" "."
    REQUIRES console fatfs
)

