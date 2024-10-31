#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <unordered_map>

using namespace std;

class Memory {
public:
    Memory();                               // Construtor
    void escrever(int endereco, int valor); // Escreve na memória
    int ler(int endereco);                  // Lê da memória
    void mostrarMemoria();                  // Exibe o estado da memória

private:
    unordered_map<int, int> memoria;        // Simulação da memória
};

#endif
