#include "laracna.hpp"
#include "movement/servo_driver2.hpp"
#include "movement/leg_move_controller.hpp"

void Laracna::build(){

    build_legs();
    cli.set_data_manager(data_man);
    cli.set_move_man(move_man);
}

void Laracna::initialize(){

    cli.start_console();

}

void Laracna::build_legs(){

    float coxa_angle_offset = stof(data_man.read_config_field("coxa_angle_offset"));
    float femur_angle_offset = stof(data_man.read_config_field("femur_angle_offset"));
    float tibia_angle_offset = stof(data_man.read_config_field("tibia_angle_offset"));

    float coxa_angle_length = stof(data_man.read_config_field("coxa_length"));
    float femur_angle_length = stof(data_man.read_config_field("femur_length"));
    float tibia_angle_length = stof(data_man.read_config_field("tibia_length"));


    // Config legs
    LegConfig leg_l0_config;
    leg_l0_config.coxa_length = coxa_angle_length;
    leg_l0_config.femur_length = femur_angle_length;
    leg_l0_config.tibia_length = tibia_angle_length;

    leg_l0_config.coxa_angle_offset = coxa_angle_offset;
    leg_l0_config.femur_angle_offset = femur_angle_offset;
    leg_l0_config.tibia_angle_offset = tibia_angle_offset;

    leg_l0_config.coxa_servo_gpio = GPIO_NUM_12;
    leg_l0_config.femur_servo_gpio = GPIO_NUM_14;
    leg_l0_config.tibia_servo_gpio = GPIO_NUM_27;
    leg_l0_config.coxa_ledc_channel = LEDC_CHANNEL_0;
    leg_l0_config.femur_ledc_channel = LEDC_CHANNEL_1;
    leg_l0_config.tibia_ledc_channel = LEDC_CHANNEL_2;
    leg_l0_config.id = "leg_l0";

    LegConfig leg_l1_config;
    leg_l1_config.coxa_length = coxa_angle_length;
    leg_l1_config.femur_length = femur_angle_length;
    leg_l1_config.tibia_length = tibia_angle_length;

    leg_l1_config.coxa_angle_offset = coxa_angle_offset;
    leg_l1_config.femur_angle_offset = femur_angle_offset;
    leg_l1_config.tibia_angle_offset = tibia_angle_offset;

    leg_l1_config.coxa_servo_gpio = GPIO_NUM_26;
    leg_l1_config.femur_servo_gpio = GPIO_NUM_25;
    leg_l1_config.tibia_servo_gpio = GPIO_NUM_33;
    leg_l1_config.coxa_ledc_channel = LEDC_CHANNEL_3;
    leg_l1_config.femur_ledc_channel = LEDC_CHANNEL_4;
    leg_l1_config.tibia_ledc_channel = LEDC_CHANNEL_5;
    leg_l1_config.id = "leg_l1";


    // create gpios and ledcs arrays
    
    LegConfig _legs[] = {leg_l0_config, leg_l1_config};

    servo_channel_t servo_channel ={
        .servo_pin = {
            leg_l0_config.coxa_servo_gpio,
            leg_l0_config.femur_servo_gpio,
            leg_l0_config.tibia_servo_gpio,

            leg_l1_config.coxa_servo_gpio,
            leg_l1_config.femur_servo_gpio,
            leg_l1_config.tibia_servo_gpio,
        
        },
        .ch = {
            leg_l0_config.coxa_ledc_channel,
            leg_l0_config.femur_ledc_channel,
            leg_l0_config.tibia_ledc_channel,
            leg_l1_config.coxa_ledc_channel,
            leg_l1_config.femur_ledc_channel,
            leg_l1_config.tibia_ledc_channel,

        }
    };
   
    uint8_t channel_number = 6;

    servo_driver2 servo(servo_channel, channel_number, LEDC_TIMER_0);


    // set legs
    leg_move_controller leg_l0(leg_l0_config);
    leg_l0.set_driver(servo);

    leg_move_controller leg_l1(leg_l1_config);
    leg_l1.set_driver(servo);

    list<leg_move_controller> legs;
    legs.push_back(leg_l0);
    legs.push_back(leg_l1);


    // set move manager
    move_man.set_legs(legs);


    
  
    

}