#include "cpu.h"
#include "memory.h"
#include "pipeline.h"
#include <iostream>

using namespace std;

int main()
{
    // Exemplo de valores nos registradores
    int registradores[32];
    registradores[0] = 10;
    registradores[1] = 20;

    // Contador de Programa (PC)
    int PC = 0;

    // Simulação de execução da instrução ADD
    cout << "Simulando execucao de uma instrucao ADD" << endl;
    InstructionFetch(PC);
    InstructionDecode();
    Execute(registradores[0], registradores[1]);
    MemoryAccess(0);
    WriteBack();

    return 0;
}
