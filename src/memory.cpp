#include "memory.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

MemoryRAM::MemoryRAM(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Não foi possível abrir o arquivo " + path);
    }
    string line;
    while (getline(file, line)) {
        _instrucoes.push_back(line);
    }
    file.close();
}

string MemoryRAM::getInstrucao(int endereco) {
    if (endereco >= 0 && endereco < _instrucoes.size()) {
        return _instrucoes[endereco];
    }
    return "";
}

size_t MemoryRAM::getSize() {
    return _instrucoes.size();
}

void MemoryRAM::escrever(int endereco, int valor) {
    _memoria[endereco] = valor;
}

MemoryCache::MemoryCache(MemoryRAM &memoryRAM) : _memoryRAM(memoryRAM) {}

void MemoryCache::escrever(int endereco, int valor) {
    _cache.push({endereco, valor});
    memoriaCheia();
}

void MemoryCache::memoriaCheia() {
    if (_cache.size() > TAM_CACHE) {
        auto dado = _cache.front();
        _cache.pop();
        _memoryRAM.escrever(dado.first, dado.second);
    }
}
