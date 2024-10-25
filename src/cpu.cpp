#include "cpu.h"

// Construtor da CPU com número de cores
CPU::CPU(int numCores)
{
    numCoresAtivos = numCores;
    coreAtivo = 0;
    // Inicializa os registradores para cada core com 32 registradores (todos com valor 0)
    registradores.resize(numCores, vector<int>(32, 0));
    cout << "--- Iniciando Simulacao com " << numCores << " Cores ---" << endl;
}

// Alternar para um core específico
void CPU::alternarCore(int coreId)
{
    if (coreId >= 0 && coreId < numCoresAtivos)
    {
        coreAtivo = coreId;
        cout << "--- Core " << coreAtivo << " Ativo ---" << endl;
    }
    else
    {
        cerr << "Erro: Core inválido!" << endl;
    }
}

// Lê o valor de um registrador
int CPU::lerRegistrador(int reg)
{
    if (reg >= 0 && reg < 32)
    {
        cout << "Lendo valor do Registrador R" << reg << " no Core " << coreAtivo << ": " << registradores[coreAtivo][reg] << endl;
        return registradores[coreAtivo][reg];
    }
    else
    {
        cerr << "Erro: Registrador invalido!" << endl;
        return -1;
    }
}

// Escreve um valor em um registrador
void CPU::escreverRegistrador(int reg, int valor)
{
    if (reg >= 0 && reg < 32)
    {
        registradores[coreAtivo][reg] = valor;
        cout << "Valor " << valor << " foi escrito no Registrador R" << reg << " no Core " << coreAtivo << endl;
    }
    else
    {
        cerr << "Erro: Registrador invalido!" << endl;
    }
}

// Escreve um valor em um endereço de memória
void CPU::escreverNaMemoria(int endereco, int valor)
{
    memoria[endereco] = valor;
    cout << "Valor " << valor << " foi armazenado no endereco " << endereco << endl;
}

// Lê um valor de um endereço de memória
int CPU::lerDaMemoria(int endereco)
{
    if (memoria.find(endereco) != memoria.end())
    {
        cout << "Lendo valor do endereco " << endereco << ": " << memoria[endereco] << endl;
        return memoria[endereco];
    }
    else
    {
        cerr << "Erro: Endereco de memoria nao encontrado!" << endl;
        return -1;
    }
}

// Exibe o estado de registradores relevantes
void CPU::mostrarEstadoRegistradores(int reg1, int reg2, int regDest)
{
    cout << "Estado atualizado dos registradores no Core " << coreAtivo << ":\n";
    cout << "R" << reg1 << ": " << registradores[coreAtivo][reg1] << endl;
    cout << "R" << reg2 << ": " << registradores[coreAtivo][reg2] << endl;
    cout << "R" << regDest << ": " << registradores[coreAtivo][regDest] << endl;
}
