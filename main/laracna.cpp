#include "laracna.hpp"

void laracna::initialize(){

    cmd.move_man = &this->move_man;
    cmd.start_console();

}