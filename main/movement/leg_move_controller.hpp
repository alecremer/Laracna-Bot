//
//  Create by Ale - 1/8/23
//

#ifndef LEG_MOVE_CONTROLLER_HPP
#define LEG_MOVE_CONTROLLER_HPP


#include <array>
#include <iostream>

#include "ik.hpp"
#include "servo_driver.hpp"
#include "servo_driver2.hpp"
#include "movement/leg_config.hpp"

/**
 * @brief Control leg motors
 */
class leg_move_controller {
public:
    leg_move_controller(const LegConfig& leg_config_ext);
    leg_move_controller(void){};

    std::string id = "";

    /**
     * @brief move leg to position
     * @param position: target of extremity of leg
     */
    void move_to_position(std::array<float, 3>&position);

    /**
     * @brief Moves coxa servo
     * @param angle: angle to move (degrees)
     */
    void move_servo_coxa(const float&angle);

    /**
     * @brief Moves femur servo
     * @param angle: angle to move (degrees)
     */
    void move_servo_femur(const float&angle);

    /**
     * @brief Moves tibia servo
     * @param angle: angle to move (degrees)
     */
    void move_servo_tibia(const float&angle);

    int read_servo_angle(const string& servo_id);

    /**
     * 
     */
    void set_driver(const servo_driver2& _driver){_servo_driver = _driver;};
    mcpwm_timer_handle_t timer;

    

private:
    IK ik_servo;
    servo_driver2 _servo_driver;
    LegConfig _leg_config;
    void move_servo_x(servo_driver&drive, const float&angle);

};


#endif
