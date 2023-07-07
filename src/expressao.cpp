#include "expressao.hpp"
#include "op.hpp"

// Função para ler uma expressão infixa e construir a árvore de expressão correspondente.
void Expressao::lerInfixa(string entrada) {
    int index = 0;
    
    try {
        // Verifica se a árvore já possui elementos e realiza a limpeza, se necessário
        if (!vazia()) {
            arvore.clean();
        }

        // Inicializa as pilhas para armazenar os nós e operadores
        Pilha<No*> pilhaNo;
        Pilha<string> pilhaOperador;

        // Percorre a string de entrada
        for (int i = 0;; i++) {
            // Caso encontre um espaço ou o fim da string, processa o token atual
            if (entrada[i] == ' ' || entrada[i] == '\0') {
                if (i != index) {
                    auto str = entrada.substr(index, i - index);
                    string tipo = lerTipoString(str);

                    // Verifica o tipo do token e realiza as operações correspondentes
                    if (tipo == "num") {
                        pilhaNo.push(new No(str));
                    } else if (tipo == "parentese_esquerdo") {
                        pilhaOperador.push(str);
                    } else if (tipo == "parentese_direito") {
                        // Processa os operadores dentro dos parênteses
                        while (lerTipoString(pilhaOperador.getTopo()) != "parentese_esquerdo") {
                            auto esq = pilhaNo.pop();
                            auto dir = pilhaNo.pop();
                            pilhaNo.push(new No(pilhaOperador.pop(), dir, esq));
                        }
                        pilhaOperador.pop();
                    } else if (tipo == "operador") {
                        // Processa os operadores fora dos parênteses
                        while (!pilhaOperador.vazia() && precedencia(pilhaOperador.getTopo()) >= precedencia(str)) {
                            auto esq = pilhaNo.pop();
                            auto dir = pilhaNo.pop();
                            pilhaNo.push(new No(pilhaOperador.pop(), dir, esq));
                        }
                        pilhaOperador.push(str);
                    }
                }
                
                // Verifica se chegou ao fim da string e encerra o loop
                if (entrada[i] == '\0') {
                    break;
                }
                
                index = i + 1;
            }
        }

        // Processa os operadores restantes
        while (!pilhaOperador.vazia()) {
            auto esq = pilhaNo.pop();
            auto dir = pilhaNo.pop();
            pilhaNo.push(new No(pilhaOperador.pop(), dir, esq));
        }

        // Atualiza a raiz da árvore com o resultado final
        arvore.setRaiz(pilhaNo.pop());
    } catch (const std::exception& e) {
        // Trata erros na leitura da expressão infixa
        std::cerr << "Erro ao ler a expressão infixa: " << e.what() << std::endl;
        throw std::runtime_error("Erro ao ler a expressão infixa");
    }
}

// Função para ler uma expressão posfixa e construir a árvore de expressão correspondente.
void Expressao::lerPosfixa(string entrada) {
    int index = 0;
    
    // Verifica se a árvore já possui elementos e realiza a limpeza, se necessário
    if (!vazia()) {
        arvore.clean();
    }

    // Inicializa a pilha para armazenar os nós
    Pilha<No*> pilha;

    // Percorre a string de entrada
    for (int i = 0;; i++) {
        // Caso encontre um espaço ou o fim da string, processa o token atual
        if (entrada[i] == ' ' || entrada[i] == '\0') {
            if (i != index) {
                auto str = entrada.substr(index, i - index);
                string tipo = lerTipoString(str);

                // Verifica o tipo do token e realiza as operações correspondentes
                if (tipo == "num") {
                    pilha.push(new No(str));
                } else if (tipo == "operador") {
                    auto esq = pilha.pop();
                    auto dir = pilha.pop();
                    auto valor_inserido = arvore.insere(str, dir, esq);
                    arvore.setRaiz(valor_inserido);
                    pilha.push(valor_inserido);
                }
            }
            
            // Verifica se chegou ao fim da string e encerra o loop
            if (entrada[i] == '\0') {
                break;
            }
            
            index = i + 1;
        }
    }
    
    // Verifica se a pilha possui apenas um elemento ou se está vazia
    // Caso contrário, limpa a árvore
    if (!(pilha.getTam() == 1) || vazia()) {
        if (!vazia()) {
            arvore.clean();
        }
    }

}

string Expressao::Infixa() {
    if (vazia()) {
        return "";
    }
    
    return arvore.inOrdemParenteses();
}

string Expressao::Posfixa() {
    if (vazia()) {
        return "";
    }
    
    return arvore.posOrdem();
}

double Expressao::resolve() {
    // Se a árvore estiver vazia, retorna 0.0
    if (vazia())
        return 0.0;

    // Cria uma pilha com a notação posfixa da expressão
    Pilha<string> pilhaPosOrdem = arvore.getPilhaPosOrdem();
    Pilha<double> pilhaAux;

    // Enquanto a pilha posfixa não estiver vazia
    while (!pilhaPosOrdem.vazia()) {
        string str = pilhaPosOrdem.pop();

        // Se o elemento for um número, converte para double e insere na pilha auxiliar
        if (lerTipoString(str) == "num") {
            double aux;
            stringstream ss;
            ss << str;
            ss >> setprecision(10) >> aux;
            pilhaAux.push(aux);
        } else if (lerTipoString(str) == "operador") {
            // Se o elemento for um operador, realiza a operação com os dois últimos elementos da pilha auxiliar
            double segundo_op = pilhaAux.pop();
            double primeiro_op = pilhaAux.pop();
            switch (str[0]) {
                case '+':
                    pilhaAux.push(primeiro_op + segundo_op);
                    break;
                case '-':
                    pilhaAux.push(primeiro_op - segundo_op);
                    break;
                case '*':
                    pilhaAux.push(primeiro_op * segundo_op);
                    break;
                case '/':
                    // Se o divisor for 0, retorna 0.0
                    if (segundo_op == 0) return 0.0;
                    pilhaAux.push(primeiro_op / segundo_op);
                    break;
            }
        }
    }

    // Retorna o resultado da expressão
    return pilhaAux.pop();
}


bool Expressao::vazia() {
    return arvore.vazia();
}
