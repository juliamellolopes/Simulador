#ifndef CPU_H
#define CPU_H

#include <unordered_map>

// Estrutura para armazenar o conjunto de registradores para cada core
struct Core
{
    int registradores[32]; // 32 registradores para cada core
};

// Classe que representa a CPU com múltiplos cores
class CPU
{
public:
    std::unordered_map<int, Core> cores; // Armazena os cores disponíveis
    int coreAtivo;                       // Índice do core ativo

    CPU(int numCores); // Construtor da CPU

    // Função para alterar o core ativo
    void alternarCore(int novoCore);

    // Função para acessar os registradores do core ativo
    int lerRegistrador(int indice);

    // Função para escrever em um registrador do core ativo
    void escreverRegistrador(int indice, int valor);

    // Nova função para mostrar o estado atual dos registradores no core ativo
    void mostrarEstadoRegistradores(int reg1, int reg2, int regDestino);
};

#endif
