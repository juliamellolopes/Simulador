#include "cpu.h"
#include "pipeline.h"
#include <iostream>

using namespace std;

int main()
{
    CPU cpu(2); // Criando uma CPU com 2 cores (você pode ajustar o número de cores conforme necessário)
    Pipeline pipeline(cpu);

        cpu.escreverRegistrador(1, 10);
    cpu.escreverRegistrador(2, 20);

    // Simulação de uma instrução ADD (código fictício)
    int instrucao = 0x040A1000; // opcode = 0 (ADD), reg1 = 1, reg2 = 2, destino = 3
    cout << "\nPipeline processando instrucao ADD...\n";
    pipeline.InstructionFetch(instrucao);
    pipeline.InstructionDecode();
    pipeline.Execute();

    // Alternar automaticamente para o Core 1
    cout << "\n--- Alternando automaticamente para Core 1 ---\n";
    cpu.alternarCore(1);

    // Escrevendo valores nos registradores do novo core (Core 1)
    cpu.escreverRegistrador(1, 50);
    cpu.escreverRegistrador(2, 30);

    // Simulação de uma instrução SUB (código fictício)
    instrucao = 0x200A1000; // opcode = 1 (SUB), reg1 = 1, reg2 = 2, destino = 3
    cout << "\nPipeline processando instrucao SUB...\n";
    pipeline.InstructionFetch(instrucao);
    pipeline.InstructionDecode();
    pipeline.Execute();

    return 0;
}
