#ifndef PIPELINE_H
#define PIPELINE_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include "cpu.h"
#include "memory.h"

using namespace std;

class Pipeline {
private:
    MemoryRAM &_memoryRAM;        // Referência para a memória principal
    CPU &_cpu;                    // Referência para a CPU
    string _instrucaoAtual;       // Instrução sendo processada
    string _opcode;               // Opcode decodificado da instrução

    queue<string> _estagioIF;     // Fila para o estágio Instruction Fetch
    queue<string> _estagioID;     // Fila para o estágio Instruction Decode
    queue<string> _estagioEX;     // Fila para o estágio Execute
    queue<string> _estagioMEM;    // Fila para o estágio Memory Access
    queue<string> _estagioWB;     // Fila para o estágio Write Back

    vector<string> tokenizar(string &instrucao); // Auxiliar para dividir instruções

public:
    Pipeline(MemoryRAM &memory, CPU &cpu);  // Construtor

    void loop();                            // Ciclo principal do pipeline
    void InstructionFetch();                // Estágio IF
    void InstructionDecode();               // Estágio ID
    void Execute();                         // Estágio EX
    void MemoryAccess();                    // Estágio MEM
    void WriteBack();                       // Estágio WB
};

#endif // PIPELINE_H
