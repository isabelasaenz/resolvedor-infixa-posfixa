#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include "pilha.tpp"
#include "arvore.hpp"
#include "op.hpp"

using namespace std;

class Expressao {
private:
    Arvore arvore;

public:
    void lerInfixa(string entrada);
    void lerPosfixa(string entrada);
    string Infixa();
    string Posfixa();
    double resolve();
    bool vazia();
};

#endif 
