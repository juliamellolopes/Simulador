#ifndef PIPELINE_H
#define PIPELINE_H

#include "cpu.h"

// Classe que representa o pipeline MIPS
class Pipeline
{
public:
    CPU &cpu;                 // Referência à CPU para acessar os cores
    int instrucaoAtual;       // A instrução que está sendo processada
    int opcode;               // O código de operação da instrução
    int operando1, operando2; // Operandos da instrução
    int registradorDestino;   // Registrador de destino para a operação

    // Construtor
    Pipeline(CPU &cpuRef);

    // Instruction Fetch (IF): busca a instrução da memória (simulada)
    void InstructionFetch(int instrucao);

    // Instruction Decode (ID): decodifica a instrução e carrega os operandos
    void InstructionDecode();

    // Execute (EX): executa a operação com base no opcode
    void Execute();
};

#endif
