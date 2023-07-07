#include <sstream>
#include <map>

#include "op.hpp"
#include "expressao.hpp"

// Verifica se a string representa um número do tipo double
bool isDouble(const string &str) {
    std::istringstream iss(str);
    double value;
    iss >> value;
    return iss.eof() && !iss.fail();
}

// Verifica se o caractere é um dos operadores ou parênteses
bool isChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

// Determina a precedência dos operadores
int precedencia(const string& op) {
    if (op == "*" || op == "/") {
        return 2;
    } else if (op == "+" || op == "-") {
        return 1;
    } else {
        return 0;
    }
}

// Determina o tipo de string da entrada
string lerTipoString(const string& str) {
    // Mapeia strings para suas respectivas instruções
    static const map<string, string> instrucoes = {
        {"LER", "ler_exp"},
        {"INFIXA", "converter_infixa"},
        {"POSFIXA", "converter_posfixa"},
        {"RESOLVE", "resolver_exp"},
    };

    // Retorna a instrução correspondente, se existir
    auto it = instrucoes.find(str);
    if (it != instrucoes.end()) {
        return it->second;
    } else if (isDouble(str)) { // Se for um número do tipo double
        return "num";
    } else if (str.length() == 1 && isChar(str[0])) { // Se for um caractere válido
        if (str[0] == '(') return "parentese_esquerdo";
        if (str[0] == ')') return "parentese_direito";
        return "operador";
    }

    // Caso não seja nenhuma das opções anteriores
    return "null";
}
