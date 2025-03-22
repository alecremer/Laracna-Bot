#include "bt_interface.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring> // Para usar strdup e free
#include "esp_log.h"

// =-=-=-=-=-=-=-=-=- Funções da Classe BTInterface -=-=-=-=-=-=-=-=-=

void BTInterface::Move(const std::string& arguments) {
    // Log de execução do comando move
    ESP_LOGE(TAG_RUN_CMD, "Running Move with the arguments: %s", arguments.c_str());
}



void BTInterface::Cmd(const std::string& arguments) { // Corrigido typo no parâmetro
    // Log de execução do comando cmd
    ESP_LOGE(TAG_RUN_CMD, "Running Cmd with the arguments: (%s)", arguments.c_str());
}

void BTInterface::Run_cmd(const std::string& command) { // Renomeado 'ordem' para 'command'
    std::vector<std::string> words;  // Vetor para armazenar palavras divididas
    std::stringstream ss(command);   // Stream para processar a string
    std::string word;                // Palavra temporária

    argc = 0; // Reinicializa contador de argumentos

    // Divide o comando em palavras
    while (ss >> word) {
        words.push_back(word);
        argc++;
    }

    // Aloca memória para os argumentos
    argv = new char*[argc];
    for (int i = 0; i < argc; ++i) {
        argv[i] = strdup(words[i].c_str()); // Converte e duplica strings
    }

    // Processa os comandos
    if (argc > 0) {
        if (std::strcmp(argv[0], "move") == 0) {
            // Concatena argumentos para o movimento
            std::string arguments;
            for (int i = 1; i < argc; ++i) { 
                if (i > 1) arguments += " ";
                arguments += argv[i];
            }
            Move(arguments);

        } else if (std::strcmp(argv[0], "cmd") == 0) {
            // Concatena argumentos para o comando genérico
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

    // Liberação de memória
    for (int i = 0; i < argc; ++i) {
        free(argv[i]); // Libera strings duplicadas
    }
    delete[] argv; // Libera array de ponteiros
}