#ifndef LIMIT_SWITCH_DRIVER_HPP
#define LIMIT_SWITCH_DRIVER_HPP

extern "C" {
    #include <freertos/FreeRTOS.h>  // Deve vir PRIMEIRO - contém as definições básicas
    #include <freertos/task.h>      // Agora os tipos serão reconhecidos
    #include "driver/gpio.h"
}

class LimitSwitchDriver{
public:

    LimitSwitchDriver();
    void init(gpio_num_t pin);
    bool read();
    ~LimitSwitchDriver();

private:

    gpio_num_t pin_;

};

#endif

