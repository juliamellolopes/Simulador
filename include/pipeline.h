#ifndef PIPELINE_H
#define PIPELINE_H

#include "cpu.h"

class Pipeline
{
public:
    Pipeline(CPU &cpu);
    void InstructionFetch(int instrucao);
    void InstructionDecode();
    void Execute();

private:
    CPU &cpu;
    int instrucaoAtual;
    int opcode;
    int reg1, reg2, regDest;
};

#endif
