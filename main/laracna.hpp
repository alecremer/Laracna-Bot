#ifndef LARACNA_HPP
#define LARACNA_HPP

#include "movement/move_manager.hpp"
#include "cmd_interface.hpp"
#include "data_manager.hpp"


/**  @brief Robot class
 * 
 *    to use: build() and initialize()
*/
class Laracna
{

private:
    /// @brief Creates servos drivers instances and legs interfaces 
    void build_legs(void);


public:
    Laracna(void){};

    /// @brief instantiate and configure robot interfaces  
    void build(void);
    /// @brief Bringup robot modules instances 
    void initialize(void); 
    
    /// @brief Provides access legs and control legs gaits
    MoveManager move_man;
    /// @brief user UART interface
    CLI cli;
    /// @brief manages robot configuration and logs files 
    data_manager data_man;
};


#endif
