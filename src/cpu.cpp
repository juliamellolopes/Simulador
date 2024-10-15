#include "cpu.h"
#include <iostream>

using namespace std;

// Unidade Lógica Aritmética (ULA)
int ULA(int operando1, int operando2, char operacao)
{
    if (operacao == '+')
        return operando1 + operando2;
    else if (operacao == '-')
        return operando1 - operando2;
    return 0;
}

// Unidade de Controle
void UnidadeControle(int opcode)
{
    switch (opcode)
    {
    case 0: // ADD
        cout << "Executando soma." << endl;
        break;
    case 1: // SUB
        cout << "Executando subtracao." << endl;
        break;
    default:
        cout << "Instrução desconhecida." << endl;
    }
}
