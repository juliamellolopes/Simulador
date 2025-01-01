#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <queue>
#include "pcb.h"
#include "memory.h"
#include "ula.h"
#include "uc.h"

class CPU {
private:
    int _PC;                     // Contador de programa
    int _coreAtivo;              // Núcleo ativo
    std::vector<REG> _cores;     // Registradores por núcleo
    PCB *processoAtual;          // Processo em execução
    std::queue<PCB *> filaProntos; // Fila de processos prontos

    MemoryRAM &_memoryRAM;
    ULA _ula;
    UC _uc;

public:
    CPU(MemoryRAM &memory);

    void incrementarPC();
    int getPC();
    int lerRegistrador(int reg);
    void escreverRegistrador(int reg, int valor);
    void executarInstrucao(int opcode);

    void carregarProcesso(PCB *pcb);
    void salvarEstadoAtual();
    void executar();
    void adicionarProcesso(PCB *pcb);
};

#endif
