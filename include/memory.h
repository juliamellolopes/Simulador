#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

#define TAM_CACHE 5

using namespace std;
class MemoryRAM {
public:
    MemoryRAM() {}                             // Construtor
    MemoryRAM(string path);                    // Construtor
    string getInstrucao(int endereco);
    size_t getSize();

    void escrever(int endereco, int valor);    // Escreve na memória
    // int ler(int endereco);                  // Lê da memória
    // void mostrarMemoria();                  // Exibe o estado da memória

private:
    unordered_map<int, int> _memoria;          // Simulação da memória
    vector<string>_instrucoes;
};

class MemoryCache {
public:
    MemoryCache() {}
    MemoryCache(MemoryRAM memoryRAM);
    void escrever(int endereco, int valor);
    void memoriaCheia();
private:
    queue<pair<int, int>> _cache;
    MemoryRAM _memoryRAM;
};