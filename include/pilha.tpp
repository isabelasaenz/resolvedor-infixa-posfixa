#pragma once
#include <iostream>
using namespace std;

// Classe Pilha que utiliza um array para armazenar elementos do tipo T
template <class T>
class Pilha {
   public:
    // Construtor da Pilha, inicializa o topo e o tamanho
    Pilha() {
        topo = -1;
        tam = 0;
    }

    // Função push, adiciona um item à pilha
    bool push(T item) {
        if (tam == MAX_TAM)
            return false; // Retorna false se a pilha estiver cheia

        topo++;
        tam++;
        itens[topo] = item;
        return true; // Retorna true se o item foi adicionado com sucesso
    }

    // Função pop, remove e retorna o item do topo da pilha
    T pop() {
        if (vazia()) {
            return T(); // Retorna um objeto vazio do tipo T se a pilha estiver vazia
        }

        T aux = itens[topo];
        topo--;
        tam--;
        return aux; // Retorna o item removido do topo da pilha
    }

    // Função getTopo, retorna o item do topo da pilha
    T getTopo() {
        return itens[topo];
    }

    // Função getTam, retorna o tamanho atual da pilha
    int getTam() {
        return tam;
    }

    // Função vazia, retorna true se a pilha estiver vazia
    bool vazia() {
        return tam == 0;
    }

    // Função clean, limpa a pilha e reinicializa o topo e o tamanho
    void clean() {
        topo = -1;
        tam = 0;
    };

    // Função print, imprime os itens da pilha na ordem inversa (do topo para a base)
    void print() {
        for (int i = tam - 1; i >= 0; i--) {
            cout << "\t|" << itens[i] << endl;
        }
    }

   private:
    int topo, tam; // Variáveis para armazenar o índice do topo e o tamanho da pilha
    static const int MAX_TAM = 1000; // Constante para o tamanho máximo da pilha
    T itens[MAX_TAM]; // Array para armazenar os itens da pilha
};
