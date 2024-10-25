#ifndef CPU_H
#define CPU_H

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class CPU
{
public:
    CPU(int numCores);                                                // Construtor para inicializar com número de cores
    void alternarCore(int coreId);                                    // Alternar entre cores
    int lerRegistrador(int reg);                                      // Lê o valor de um registrador
    void escreverRegistrador(int reg, int valor);                     // Escreve um valor em um registrador
    void escreverNaMemoria(int endereco, int valor);                  // Escreve na memória
    int lerDaMemoria(int endereco);                                   // Lê da memória
    void mostrarEstadoRegistradores(int reg1, int reg2, int regDest); // Exibe o estado dos registradores

private:
    int numCoresAtivos;
    int coreAtivo;
    vector<vector<int>> registradores; // Matriz de registradores para múltiplos cores
    unordered_map<int, int> memoria;   // Simulação de memória
};

#endif
