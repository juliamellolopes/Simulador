#include "memory.h"

// Construtor da memória
Memory::Memory()
{
    // Inicialização da memória, se necessário
    // Não há necessidade de inicialização explícita para unordered_map
}

// Escreve um valor em um endereço de memória
void Memory::escrever(int endereco, int valor)
{
    memoria[endereco] = valor;
    cout << "Valor " << valor << " foi armazenado no endereco " << endereco << endl;
}

// Lê um valor de um endereço de memória
int Memory::ler(int endereco)
{
    if (memoria.find(endereco) != memoria.end())
    {
        return memoria[endereco];
    }
    else
    {
        cerr << "Erro: Endereco de memoria nao encontrado!" << endl;
        return -1; // Valor inválido para indicar erro
    }
}

// Exibe o estado da memória
void Memory::mostrarMemoria()
{
    cout << "\n--- Estado Atual da Memória ---\n";
    for (const auto &entry : memoria)
    {
        cout << "Endereco " << entry.first << ": " << entry.second << endl;
    }
}
