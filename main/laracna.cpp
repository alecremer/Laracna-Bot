#include "laracna.hpp"
#include "movement/servo_driver2.hpp"
#include "movement/leg_move_controller.hpp"

#define COXA_LENGTH 1
#define FEMUR_LENGTH 1
#define TIBIA_LENGTH 1

void laracna::initialize(){

    cmd.move_man = &this->move_man;
    cmd.start_console();

}

void laracna::build_legs(){


    // Config legs
    leg_config leg_1;
    leg_1.coxa_length = COXA_LENGTH;
    leg_1.femur_length = FEMUR_LENGTH;
    leg_1.tibia_length = TIBIA_LENGTH;
    leg_1.coxa_servo_gpio = GPIO_NUM_12;
    leg_1.femur_servo_gpio = GPIO_NUM_14;
    leg_1.tibia_servo_gpio = GPIO_NUM_27;
    leg_1.id = "leg_l0";

    leg_config leg_2;
    leg_1.coxa_length = COXA_LENGTH;
    leg_1.femur_length = FEMUR_LENGTH;
    leg_1.tibia_length = TIBIA_LENGTH;
    leg_1.coxa_servo_gpio = GPIO_NUM_26;
    leg_1.femur_servo_gpio = GPIO_NUM_25;
    leg_1.tibia_servo_gpio = GPIO_NUM_33;
    leg_1.id = "leg_l1";


    // create gpios and ledcs arrays
    
    leg_config _legs[] = {leg_1, leg_2};

    gpio_num_t servo_gpios[]{
        leg_1.coxa_servo_gpio,
        leg_1.femur_servo_gpio,
        leg_1.tibia_servo_gpio,

        leg_2.coxa_servo_gpio,
        leg_2.femur_servo_gpio,
        leg_2.tibia_servo_gpio,
    
    };

     ledc_channel_t ledc_ch[]{
        LEDC_CHANNEL_0,
        LEDC_CHANNEL_1,
        LEDC_CHANNEL_2,
        LEDC_CHANNEL_3,
        LEDC_CHANNEL_4,
        LEDC_CHANNEL_5,
    };
    
    servo_driver2 servo(servo_gpios, ledc_ch, LEDC_TIMER_0);
    
    // gpio_num_t servo_gpios[]{
    //     GPIO_NUM_12,
    //     GPIO_NUM_14,
    //     GPIO_NUM_27,
    //     GPIO_NUM_26,
    //     GPIO_NUM_25,
    //     GPIO_NUM_33,
    //     GPIO_NUM_32,
    //     GPIO_NUM_15,
    // };
    
    // ledc_channel_t ledc_ch[]{
    //     LEDC_CHANNEL_0,
    //     LEDC_CHANNEL_1,
    //     LEDC_CHANNEL_2,
    //     LEDC_CHANNEL_3,
    //     LEDC_CHANNEL_4,
    //     LEDC_CHANNEL_5,
    //     LEDC_CHANNEL_6,
    //     LEDC_CHANNEL_7,
    // };
    
    

}