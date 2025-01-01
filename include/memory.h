#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>

#define TAM_CACHE 5

class MemoryRAM {
private:
    std::vector<std::string> _instrucoes;
    std::map<int, int> _memoria;

public:
    MemoryRAM(std::string path);
    std::string getInstrucao(int endereco);
    size_t getSize();
    void escrever(int endereco, int valor);
};

class MemoryCache {
private:
    std::queue<std::pair<int, int>> _cache;
    MemoryRAM &_memoryRAM;

public:
    MemoryCache(MemoryRAM &memoryRAM);
    void escrever(int endereco, int valor);
    void memoriaCheia();
};

#endif
