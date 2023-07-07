#ifndef ARVORE_HPP
#define ARVORE_HPP
#include <string>
#include "pilha.tpp"

using namespace std;

class No {
public:
    string dado;
    No* esq;
    No* dir;
    
    No();
    No(string valor);
    No(string valor, No* e, No* d);
    
    string getDado();
};

class Arvore {
public:
    No* raiz;
    
    Arvore();
    void setRaiz(No* no);
    No* insere(string dado, No* esq = nullptr, No* dir = nullptr);
    
    string preOrdem();
    string inOrdemParenteses();
    string posOrdem();
    
    Pilha<string> getPilhaInOrdem();
    Pilha<string> getPilhaPosOrdem();
    
    bool vazia();
    void clean();
    
    ~Arvore();
    
private:
    string preOrdem(No*& p);
    string inOrdemParenteses(No*& p);
    string posOrdem(No*& p);
    
    void pilhaInOrdem(No*& p, Pilha<string>& aux);
    void pilhaPosOrdem(No*& p, Pilha<string>& aux);
    void apaga(No*& p);
};

#endif