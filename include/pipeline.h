#ifndef PIPELINE_H
#define PIPELINE_H

#include "memory.h"
#include "cpu.h"

#define DBG(x) std::cerr << #x << " = " << (x) <<std::endl;

class Pipeline {
public:
    Pipeline() {}
    Pipeline(MemoryRAM &memory, CPU &cpu);
    void InstructionFetch();
    void InstructionDecode();
    void Execute(string code);
    vector<string>tokenizar(string &instrucao);
    void loop();

private:
    string _instrucaoAtual;
    string _opcode;
    MemoryRAM _memoryRAM;
    CPU _cpu;
};

#endif
