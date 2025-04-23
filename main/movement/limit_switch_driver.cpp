#include "limit_switch_driver.hpp"

LimitSwitchDriver::LimitSwitchDriver(){} 

void LimitSwitchDriver::init(gpio_num_t pin){

    esp_rom_gpio_pad_select_gpio(pin);          //selecionando pino         
    gpio_set_direction(pin, GPIO_MODE_INPUT);   //setando pino como input

}

bool LimitSwitchDriver::read(){

    if(gpio_get_level(pin_) == 1){
        return true;
    }else{
        return false;
    }

}

LimitSwitchDriver::~LimitSwitchDriver(){}
