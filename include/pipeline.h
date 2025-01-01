#ifndef PIPELINE_H
#define PIPELINE_H

#include "memory.h"
#include "cpu.h"
#include <string>
#include <vector>
#include <sstream>

class Pipeline {
private:
    MemoryRAM &_memoryRAM;
    CPU &_cpu;
    std::string _instrucaoAtual;
    std::string _opcode;

    int obterIndiceRegistrador(const std::string &reg);

public:
    Pipeline(MemoryRAM &memory, CPU &cpu);
    void loop();
    void InstructionFetch();
    void InstructionDecode();
    void Execute(std::string code);
    std::vector<std::string> tokenizar(std::string &instrucao);
};

#endif
