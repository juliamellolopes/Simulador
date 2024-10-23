#include "cpu.h"
#include <iostream>

using namespace std;

// Construtor da CPU: Inicializa o número de cores
CPU::CPU(int numCores)
{
    for (int i = 0; i < numCores; i++)
    {
        cores[i] = Core();
    }
    coreAtivo = 0; // Core 0 é o ativo por padrão
}

// Função para alterar o core ativo
void CPU::alternarCore(int novoCore)
{
    if (cores.find(novoCore) != cores.end())
    {
        coreAtivo = novoCore;
        cout << "\nCore alternado para: Core " << novoCore << endl;
    }
    else
    {
        cout << "\nErro: Core " << novoCore << " não existe!" << endl;
    }
}

// Função para ler o valor de um registrador do core ativo
int CPU::lerRegistrador(int indice)
{
    return cores[coreAtivo].registradores[indice];
}

// Função para escrever um valor em um registrador do core ativo
void CPU::escreverRegistrador(int indice, int valor)
{
    cores[coreAtivo].registradores[indice] = valor;
    cout << "Valor " << valor << " foi escrito no Registrador R" << indice << " no Core " << coreAtivo << endl;
}

// Função para mostrar o estado dos registradores relevantes após a execução de uma instrução
void CPU::mostrarEstadoRegistradores(int reg1, int reg2, int regDestino)
{
    cout << "\nEstado atualizado dos registradores no Core " << coreAtivo << ":\n";
    cout << "R" << reg1 << ": " << cores[coreAtivo].registradores[reg1] << endl;
    cout << "R" << reg2 << ": " << cores[coreAtivo].registradores[reg2] << endl;
    cout << "R" << regDestino << ": " << cores[coreAtivo].registradores[regDestino] << endl;
}
