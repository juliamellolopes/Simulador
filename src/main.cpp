#include "cpu.h"
#include "pipeline.h"
#include <iostream>

using namespace std;

int main()
{
    int numCores = 4; // Define a quantidade de cores
    CPU cpu(numCores);
    Pipeline pipeline(cpu);

    cout << "\n--- Iniciando Simulacao ---\n";

    for (int core = 0; core < numCores; core++)
    {
        cout << "\n--- Core " << core << " Ativo ---\n";
        cpu.alternarCore(core);

        cpu.escreverRegistrador(1, (core + 1) * 10); // Escrevendo valores em R1
        cpu.escreverRegistrador(2, (core + 1) * 20); // Escrevendo valores em R2

        // Instrução ADD (ADD R3, R1, R2)
        int instrucaoADD = 0x00221820; // opcode = 0 (ADD), reg1 = 1, reg2 = 2, destino = 3
        cout << "\nPipeline processando instrucao ADD no Core " << core << "...\n";
        pipeline.InstructionFetch(instrucaoADD);
        pipeline.InstructionDecode();
        pipeline.Execute();

        // Instrução SUB (SUB R3, R1, R2)
        int instrucaoSUB = 0x00221822; // opcode = 1 (SUB), reg1 = 1, reg2 = 2, destino = 3
        cout << "\nPipeline processando instrucao SUB no Core " << core << "...\n";
        pipeline.InstructionFetch(instrucaoSUB);
        pipeline.InstructionDecode();
        pipeline.Execute();
    }

    cout << "\n--- Fim da Simulacao ---\n";
    return 0;
}
