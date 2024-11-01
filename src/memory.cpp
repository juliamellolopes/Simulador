#include "../include/memory.h"

MemoryCache::MemoryCache(MemoryRAM memoryRAM) {
    _memoryRAM = memoryRAM;
}

void MemoryCache::escrever(int endereco, int valor) {
    cout << "Guadando informação na Cache..." << endl;
    _cache.push(make_pair(endereco, valor));

    if (_cache.size() >= TAM_CACHE) {
        cout << "[Cache cheia]... Guardando o primeiro valor na memoria RAM" << endl;
        memoriaCheia();
    }
}

void MemoryCache::memoriaCheia() {
    auto retirar = _cache.front();
    _cache.pop();
    _memoryRAM.escrever(retirar.first, retirar.second);
}

// Construtor da memória
MemoryRAM::MemoryRAM(string path) {
    ifstream instrFile(path);
    string linha;

    if (instrFile.is_open()) {
        while (getline(instrFile, linha)) {
            _instrucoes.push_back(linha);
        }
    } else {
        cerr << "Erro ao abrir o arquivo de instruções." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Instrucoes carregadas!" << endl;
}

string MemoryRAM::getInstrucao(int endereco) {
    return _instrucoes.at(endereco);
}

size_t MemoryRAM::getSize() {
    return _instrucoes.size();
}

// Escreve um valor em um endereço de memória
void MemoryRAM::escrever(int endereco, int valor) {
    _memoria[endereco] = valor;
    cout << "Valor " << valor << " foi armazenado no endereco " << endereco << endl;
}

// // Lê um valor de um endereço de memória
// int MemoryRAM::ler(int endereco) {
//     if (memoria.find(endereco) != memoria.end()) {
//         return memoria[endereco];
//     } else {
//         cerr << "Erro: Endereco de memoria nao encontrado!" << endl;
//         return -1; // Valor inválido para indicar erro
//     }
// }

// // Exibe o estado da memória
// void MemoryRAM::mostrarMemoria() {
//     cout << "\n--- Estado Atual da Memória ---\n";
//     for (const auto &entry : memoria) {
//         cout << "Endereco " << entry.first << ": " << entry.second << endl;
//     }
// }
