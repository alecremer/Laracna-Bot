#include <iostream>
#include <sstream>
#include <vector>

void move(const std::string& parametros){
    std::cout << "Executando 'move' com os parâmetros: " << parametros << std::endl;
}

void cmd(const std::string& parametros){
    std::cout << "Executando 'cmd' com os parâmetros: " << parametros << std::endl;
}

void executarComando(const std::string& ordem){
    
    std::vector<std::string> palavras;  // Cria um vetor de string
    std::stringstream ss(ordem);        // Não entendo direito ainda
    std::string palavra;                // String temporaria para armazenar as palavras para colocar no vetor

    while (ss >> palavra){
        palavras.push_back(palavra);
    }

    // Verifica se o comando esta vazio
    if (!palavra.empty()){
        // testa se a primeira palavra é move e chama a função move se for move kk
        if (palavras[0] == "move"){
            std::string parametros = ordem.substr(ordem.find(" ") + 1);
            move(parametros);
        }

        // igual so que pra cmd
        else if(palavras[0] == "cmd"){
            std::string parametros = ordem.substr(ordem.find(" ") + 1);
            cmd(parametros);
        }

        else {
            std::cout << "Comando invalido ou não cadastrado" << std::endl;
        }
    }

    else{
        std::cout << "Comando vazio" << std::endl;
    }
}

int main() {
    std::string ordem = "move leg0 coxa 45 -n";
    executarComando(ordem);

    ordem = "cmd teste de comando";
    executarComando(ordem);

    return 0;
}