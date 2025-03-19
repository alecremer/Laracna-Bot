#include <iostream>
#include <sstream>
#include <vector>
#include <cstring> // Para usar strdup e free

extern "C" {
    #include "esp_log.h"
}

#ifndef BT_INTERFACE_HPP
#define BT_INTERFACE_HPP

#define TAG_RUN_CMD "RunCmd" // Define uma tag para os logs

class BTInterface
{
private:

    int argc;
    char** argv = nullptr;               // Aloca memória para o array de ponteiros
    std::vector<std::string> vet_work;   // Cria um vetor de string
    std::string work;                    // String temporaria para armazenar as palavras para colocar no vetor

public:

    BTInterface(void){}
    void Move(const std::string& arguments);
    void Cmd(const std::string& arguments);
    void Run_cmd(const std::string& command);
};

#endif
