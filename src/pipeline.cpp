#include "pipeline.h"
#include <iostream>

using namespace std;

Pipeline::Pipeline(CPU &cpu) : cpu(cpu)
{
    instrucaoAtual = 0;
    opcode = 0;
    reg1 = reg2 = regDest = 0;
}

// Etapa de busca
void Pipeline::InstructionFetch(int instrucao)
{
    instrucaoAtual = instrucao;
    cout << "\n--------- Pipeline Stage: Instruction Fetch ---------\n";
    cout << "[IF] Buscando instrucao... Instrucao carregada = " << instrucaoAtual << endl;
}

// Etapa de decodificação
void Pipeline::InstructionDecode()
{
    opcode = (instrucaoAtual >> 26) & 0x3F; // Extrai o opcode
    reg1 = (instrucaoAtual >> 21) & 0x1F;
    reg2 = (instrucaoAtual >> 16) & 0x1F;
    regDest = (instrucaoAtual >> 11) & 0x1F;
    cout << "\n--------- Pipeline Stage: Instruction Decode ---------\n";
    cout << "[ID] Decodificando instrucao... Opcode = " << opcode << endl;
    cout << "Registradores usados: R" << reg1 << " = " << cpu.lerRegistrador(reg1) << ", R" << reg2 << " = " << cpu.lerRegistrador(reg2) << endl;
    cout << "Resultado será armazenado no Registrador R" << regDest << endl;
}

// Etapa de execução
void Pipeline::Execute()
{
    int valor1 = cpu.lerRegistrador(reg1);
    int valor2 = cpu.lerRegistrador(reg2);
    int resultado;

    cout << "\n--------- Pipeline Stage: Execution ---------\n";

    switch (opcode)
    {
    case 0: // ADD
        resultado = valor1 + valor2;
        cout << "[EX] Executando operacao ADD: " << valor1 << " + " << valor2 << " = " << resultado << endl;
        break;
    case 1: // SUB
        resultado = valor1 - valor2;
        cout << "[EX] Executando operacao SUB: " << valor1 << " - " << valor2 << " = " << resultado << endl;
        break;
    case 2: // MULT
        resultado = valor1 * valor2;
        cout << "[EX] Executando operacao MULT: " << valor1 << " * " << valor2 << " = " << resultado << endl;
        break;
    case 3: // DIV
        if (valor2 != 0)
        {
            resultado = valor1 / valor2;
            cout << "[EX] Executando operacao DIV: " << valor1 << " / " << valor2 << " = " << resultado << endl;
        }
        else
        {
            cerr << "[EX] Erro: Divisão por zero!" << endl;
            return;
        }
        break;
    default:
        cerr << "[EX] Operacao invalida!" << endl;
        return;
    }

    cpu.escreverRegistrador(regDest, resultado);
}
