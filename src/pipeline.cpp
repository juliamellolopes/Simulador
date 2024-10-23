#include "pipeline.h"
#include <iostream>

using namespace std;

// Construtor do pipeline MIPS
Pipeline::Pipeline(CPU &cpuRef) : cpu(cpuRef), reg1(0), reg2(0) {}

// Instruction Fetch (IF): busca a instrução da memória (simulada aqui)
void Pipeline::InstructionFetch(int instrucao)
{
    instrucaoAtual = instrucao;
    cout << "\n--------- Pipeline Stage: Instruction Fetch ---------\n";
    cout << "[IF] Buscando instrucao... Instrucao carregada = " << instrucaoAtual << endl;
}

// Instruction Decode (ID): decodifica a instrução e carrega os operandos
void Pipeline::InstructionDecode()
{
    cout << "\n--------- Pipeline Stage: Instruction Decode ---------\n";

    // Extração correta dos bits da instrução
    opcode = (instrucaoAtual & 0x0000003F);                   // Extração correta do opcode (últimos 6 bits)
    reg1 = (instrucaoAtual & 0x03E00000) >> 21;               // Registrador fonte 1
    reg2 = (instrucaoAtual & 0x001F0000) >> 16;               // Registrador fonte 2
    registradorDestino = (instrucaoAtual & 0x0000F800) >> 11; // Registrador de destino

    operando1 = cpu.lerRegistrador(reg1);
    operando2 = cpu.lerRegistrador(reg2);

    cout << "[ID] Decodificando instrucao... Opcode = " << opcode << endl;
    cout << "Registradores usados: R" << reg1 << " = " << operando1 << ", R" << reg2 << " = " << operando2 << endl;
    cout << "Resultado sera armazenado no Registrador R" << registradorDestino << endl;
}

// Execute (EX): executa a operação com base no opcode
void Pipeline::Execute()
{
    cout << "\n--------- Pipeline Stage: Execution ---------\n";

    int resultado = 0;
    switch (opcode)
    {
    case 32: // ADD (o opcode de ADD na MIPS é 32 em decimal)
        resultado = operando1 + operando2;
        cout << "[EX] Executando operacao ADD: " << operando1 << " + " << operando2 << " = " << resultado << endl;
        break;
    case 34: // SUB (o opcode de SUB na MIPS é 34 em decimal)
        resultado = operando1 - operando2;
        cout << "[EX] Executando operacao SUB: " << operando1 << " - " << operando2 << " = " << resultado << endl;
        break;
    default:
        cout << "[EX] Erro: Opcode desconhecido!" << endl;
        return;
    }

    // Write Back: escreve o resultado no registrador de destino
    cpu.escreverRegistrador(registradorDestino, resultado);

    // Mostrar o estado dos registradores relevantes após a execução
    cpu.mostrarEstadoRegistradores(reg1, reg2, registradorDestino);
}