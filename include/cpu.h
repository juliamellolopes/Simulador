#ifndef CPU_H
#define CPU_H

#include <vector>
#include "memory.h"
#include "ula.h"
#include "uc.h"

using namespace std;

// Definição de registradores e núcleos
#define TAM_R 8   // Número de registradores por núcleo
#define TAM_C 2   // Número de núcleos

class REG {
public:
    REG();                                // Construtor padrão
    vector<int> _registradores;          // Registradores de um núcleo
};

class CPU {
public:
    CPU(MemoryRAM &memory);               // Construtor que recebe a memória RAM
    int lerRegistrador(int reg);          // Lê um valor de um registrador
    void escreverRegistrador(int reg, int valor); // Escreve um valor em um registrador
    void incrementarPC();                 // Incrementa o contador de programa (PC)
    int getPC();                          // Obtém o valor do contador de programa
    void executarInstrucao(int opcode);   // Executa uma instrução com base no opcode

private:
    int _PC;                              // Contador de programa
    int _coreAtivo;                       // Núcleo atualmente ativo
    vector<REG> _cores;                   // Vetor de núcleos
    MemoryRAM _memoryRAM;                 // Referência à memória RAM
    ULA _ula;                             // Unidade Lógica Aritmética
    UC _uc;                               // Unidade de Controle
};

#endif
