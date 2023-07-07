// Inclusão de bibliotecas
#include <iostream>
#include <string.h>
#include <fstream>
#include <map>

// Inclusão de arquivos de cabeçalho personalizados
#include "expressao.hpp"
#include "op.hpp"

using namespace std;

// Declaração de variáveis globais
Expressao expressao;

// Função para ler e interpretar a entrada
void lerEntrada(string& entrada) {
    int index = 0;
    char espaco = ' ';
    string modo_leitura = "";

    try {
        // Mapeamento de instruções para funções correspondentes
        static const map<string, string> instrucoes = {
            {"LER", "ler_exp"},
            {"INFIXA", "converter_infixa"},
            {"POSFIXA", "converter_posfixa"},
            {"RESOLVE", "resolver_exp"},
        };

        // Função lambda para buscar o tipo de string correspondente à instrução
        auto lerTipoString = [&](const string& str) -> string {
            auto it = instrucoes.find(str);
            if (it != instrucoes.end()) {
                return it->second;
            }
            return "";
        };

        // Loop para processar a entrada e executar as instruções correspondentes
        for (int i = 0;; i++) {
            if (entrada[i] == espaco || entrada[i] == '\0') {
                if (i != index) {
                    string str = entrada.substr(index, i - index);
                    string tipo_string = lerTipoString(str);

                    // Identificar e executar instruções com base no tipo_string
                    if (tipo_string == "ler_exp") {
                        modo_leitura = "ler";
                    } else if (modo_leitura == "ler") {
                        if (tipo_string == "converter_infixa") {
                            expressao.lerInfixa(entrada.substr(index, entrada.length() - index));
                            cout << "EXPRESSAO OK: " << expressao.Infixa() << endl;
                        } else if (tipo_string == "converter_posfixa") {
                            expressao.lerPosfixa(entrada.substr(index, entrada.length() - index));
                            cout << "EXPRESSAO OK: " << expressao.Posfixa() << endl;
                            break;
                        }
                    } else if (tipo_string == "converter_infixa") {
                        cout << "INFIXA: " << expressao.Infixa() << endl;
                    } else if (tipo_string == "converter_posfixa") {
                        cout << "POSFIXA: " << expressao.Posfixa() << endl;
                    } else if (tipo_string == "resolver_exp") {
                        cout << "VAL: " << fixed << setprecision(6) << expressao.resolve() << endl;
                    }
                }
                if (entrada[i] == '\0') break;
                index = i + 1;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao ler entrada: " << e.what() << std::endl;
    }
}

// Função principal
int main(int argc, char const *argv[]) {
    string entrada;
    string arquivo_entrada = (argc > 1) ? argv[1] : "entrada.txt";

    try {
        // Abrir arquivo de entrada
        ifstream arquivo(arquivo_entrada);
        if (!arquivo.is_open()) {
            throw std::runtime_error("ERRO: NÃO FOI POSSÍVEL ABRIR O ARQUIVO " + arquivo_entrada);
        }

        // Ler e processar cada linha do arquivo
        while (getline(arquivo, entrada)) {
            lerEntrada(entrada);
        }

        // Fechar arquivo
        arquivo.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
