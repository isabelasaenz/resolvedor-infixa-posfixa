#include "arvore.hpp"

// Implementação da classe No
No::No() {
    dado = "";
    esq = nullptr;
    dir = nullptr;
}

// Construtor com valor
No::No(string valor) : dado(valor) {
    esq = nullptr;
    dir = nullptr;
}

// Construtor com valor e nós esquerdo e direito
No::No(string valor, No* e, No* d) : dado(valor), esq(e), dir(d) {

}

// Retorna o valor do nó
string No::getDado() {
    return dado;
}

// Implementação da classe Arvore
Arvore::Arvore() {
    raiz = nullptr;
}

// Define a raiz da árvore
void Arvore::setRaiz(No* no) {
    raiz = no;
}

// Funções de inserção
No* Arvore::insere(string dado, No* esq, No* dir) {
    No* novo_no;
    try {
        novo_no = new No(dado);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Erro na alocação de memória: " << e.what() << std::endl;
        return nullptr;
    }
    novo_no->esq = esq;
    novo_no->dir = dir;
    return novo_no;
}

// Funções de travessia
// Pré-ordem
string Arvore::preOrdem() {
    if (vazia())
        return "";
    return preOrdem(raiz);
}

// Em ordem com parênteses
string Arvore::inOrdemParenteses() {
    if (vazia())
        return "";
    return inOrdemParenteses(raiz);
}

// Pós-ordem
string Arvore::posOrdem() {
    if (vazia())
        return "";
    return posOrdem(raiz);
}

// Funções de pilha
// Pilha em ordem
Pilha<string> Arvore::getPilhaInOrdem() {
    Pilha<string> pilha;
    if (vazia())
        return pilha;
    pilhaInOrdem(raiz, pilha);
    return pilha;
}

// Pilha pós-ordem
Pilha<string> Arvore::getPilhaPosOrdem() {
    Pilha<string> pilha;
    if (vazia())
        return pilha;
    pilhaPosOrdem(raiz, pilha);
    return pilha;
}

// Funções auxiliares
// Verifica se a árvore está vazia
bool Arvore::vazia() {
    return raiz == nullptr;
}

// Limpa a árvore
void Arvore::clean() {
    if (vazia())
        return;
    apaga(raiz);
    raiz = nullptr;
}

// Funções de travessia recursivas
string Arvore::preOrdem(No*& p) {
    if (p != nullptr) {
        return p->dado + " " + preOrdem(p->esq) + preOrdem(p->dir);
    }
    return "";
}

string Arvore::inOrdemParenteses(No*& p) {
    if (p != nullptr) {
        return "( " + inOrdemParenteses(p->esq) + p->dado + " " + inOrdemParenteses(p->dir) + ") ";
    }
    return "";
}

string Arvore::posOrdem(No*& p) {
    if (p != nullptr) {
        return posOrdem(p->esq) + posOrdem(p->dir) + p->dado + " ";
    }
    return "";
}

// Funções de pilha recursivas
void Arvore::pilhaInOrdem(No*& p, Pilha<string>& aux) {
    if (p != nullptr) {
        pilhaInOrdem(p->dir, aux);
        aux.push(p->dado);
        pilhaInOrdem(p->esq, aux);
    }
}

void Arvore::pilhaPosOrdem(No*& p, Pilha<string>& aux) {
    if (p != nullptr) {
        aux.push(p->dado);
        pilhaPosOrdem(p->dir, aux);
        pilhaPosOrdem(p->esq, aux);
    }
}

// Função para apagar a árvore
void Arvore::apaga(No*& p) {
    if (p != nullptr) {
        apaga(p->esq);
        apaga(p->dir);
        delete p;
    }
}

// Destrutor da classe Arvore
Arvore::~Arvore() {
    clean();
}

