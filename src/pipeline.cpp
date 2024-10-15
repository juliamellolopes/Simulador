#include "pipeline.h"
#include "memory.h"
#include "cpu.h"
#include <iostream>

using namespace std;

// Simulação dos cinco estágios do pipeline MIPS
void InstructionFetch(int &PC)
{
    cout << "Buscando instrução da memória no endereço: " << PC << endl;
    PC += 4; // Simulação de busca da próxima instrução
}

void InstructionDecode()
{
    cout << "Decodificando instrução..." << endl;
}

void Execute(int operando1, int operando2)
{
    cout << "Executando operação na ULA." << endl;
    int resultado = ULA(operando1, operando2, '+');
    cout << "Resultado da execução: " << resultado << endl;
}

void MemoryAccess(int endereco)
{
    cout << "Acessando memória no endereço: " << endereco << endl;
    lerMemoria(endereco);
}

void WriteBack()
{
    cout << "Escrevendo resultado de volta no registrador." << endl;
}
