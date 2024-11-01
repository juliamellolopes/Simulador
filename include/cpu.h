#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <unordered_map>

#include "memory.h"
// #include "pipeline.h"

using namespace std;

#ifndef REG_H
#define REG_H

#define TAM_R 8
#define TAM_C 2

class REG {
public:
    REG();
    vector<int> _registradores;

private:
};

#endif
class CPU {
public:
    CPU() {}                                                           // Construtor para inicializar com número de cores
    CPU(MemoryRAM &memory);                                              // Construtor para inicializar com número de cores
    int lerRegistrador(int reg);                                      // Lê o valor de um registrador
    void escreverRegistrador(int reg, int valor);                     // Escreve um valor em um registrador
    void escreverNaMemoria(int endereco);                             // Escreve na memória
    int ULA(int var1, int var2, char var3);                           // Unidade logica aritimetica  
    void UC(int opcode);                                              // Unidade de controle 
    int getPC();
    void incrementaPC();
    int _reg1, _reg2, _regDest;

private:
    int _coreAtivo;
    int _PC;
    vector<REG> _cores;
    MemoryRAM _memoryRAM;
    MemoryCache _memoryCache;
};

#endif
