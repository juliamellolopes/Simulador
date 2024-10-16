#include "pipeline.h"
#include <iostream>

using namespace std;

// Construtor do pipeline MIPS
Pipeline::Pipeline(CPU &cpuRef) : cpu(cpuRef) {}

// Instruction Fetch (IF): busca a instrução da memória (simulada aqui)
void Pipeline::InstructionFetch(int instrucao)
{
    instrucaoAtual = instrucao;
    cout << "\n[IF] Buscando instrucao... Instrucao carregada = " << instrucaoAtual << endl;
}

// Instruction Decode (ID): decodifica a instrução e carrega os operandos
void Pipeline::InstructionDecode()
{
    // Simulando que os 3 primeiros bits são o opcode
    opcode = (instrucaoAtual & 0xE0000000) >> 29;
    // Simulando que os próximos bits indicam os registradores fonte e destino
    int reg1 = (instrucaoAtual & 0x1F00000) >> 20;
    int reg2 = (instrucaoAtual & 0xF8000) >> 15;
    registradorDestino = (instrucaoAtual & 0x7C00) >> 10;

    // Carrega os valores dos registradores do core ativo
    operando1 = cpu.lerRegistrador(reg1);
    operando2 = cpu.lerRegistrador(reg2);

    cout << "[ID] Decodificando instrucao... Opcode = " << opcode << endl;
    cout << "Registradores usados: R" << reg1 << " = " << operando1 << ", R" << reg2 << " = " << operando2 << endl;
    cout << "Resultado sera armazenado no Registrador R" << registradorDestino << endl;
}

// Execute (EX): executa a operação com base no opcode
void Pipeline::Execute()
{
    int resultado = 0;
    switch (opcode)
    {
    case 0: // ADD
        resultado = operando1 + operando2;
        cout << "[EX] Executando operacao ADD: " << operando1 << " + " << operando2 << " = " << resultado << endl;
        break;
    case 1: // SUB
        resultado = operando1 - operando2;
        cout << "[EX] Executando operacao SUB: " << operando1 << " - " << operando2 << " = " << resultado << endl;
        break;
    default:
        cout << "[EX] Erro: Opcode desconhecido!" << endl;
        return;
    }

    // Write Back: escreve o resultado no registrador de destino
    cpu.escreverRegistrador(registradorDestino, resultado);
}
