#include <iostream>
#include <sstream>
#include <vector>
#include <cstring> // Para usar strdup e free
#include "esp_log.h"

#define TAG "RunCmd" // Define uma tag para os logs

void Move(const std::string& arguments){
    ESP_LOGE(TAG, "Running Move with the arguments: %s", arguments.c_str());
    }

void Cmd(const std::string& argumrnts){
    ESP_LOGE(TAG,"Running Cmd with the arguments: (%s)", argumrnts.c_str());
}

void Run_cmd(const std::string& ordem){
    
    std::vector<std::string> palavras;  // Cria um vetor de string
    std::stringstream ss(ordem);        // Stringstream para separar palavras
    std::string palavra;                // String temporaria para armazenar as palavras para colocar no vetor

    int argc = 0;   // Variável para armazenar número de de palavras da string

    while (ss >> palavra){
        palavras.push_back(palavra);
        argc ++;
    }

    char** argv = new char*[argc]; // Aloca memória para o array de ponteiros
    for (int i = 0; i < argc; ++i) {
        argv[i] = strdup(palavras[i].c_str()); // Converte std::string para char* e duplica
    }


    if (argc > 0) {
        if (std::strcmp(argv[0], "move") == 0) {

            std::string arguments;
            for (int i = 1; i < argc; ++i) { 
                if (i > 1) arguments += " ";
                arguments += argv[i];
            }
            Move(arguments);

        } else if (std::strcmp(argv[0], "cmd") == 0) {
            std::string arguments;
            for (int i = 1; i < argc; ++i) {
                if (i > 1) arguments += " ";
                arguments += argv[i];
            }
            Cmd(arguments);
        } else {
            std::cout << "Comando inválido ou não cadastrado" << std::endl;
        }
    } else {
        std::cout << "Comando vazio" << std::endl;
    }

    // Liberar a memória alocada para argv
    for (int i = 0; i < argc; ++i) {
        free(argv[i]); // Libera a memória de cada string duplicada
    }
    delete[] argv; // Libera o array de ponteiros

}

int Text_Interface() {
    std::string ordem = "move leg0 coxa 45 -n";
    Run_cmd(ordem);

    ordem = "cmd teste de comando";
    Run_cmd(ordem);

    return 0;
}