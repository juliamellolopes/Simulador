#include "memory.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> memoria(1024, 0); // 1024 posições de memória
queue<int> cache;             // Cache FIFO
const int TAMANHO_CACHE = 4;  // Tamanho da cache

// Função para ler a memória com uso de cache
int lerMemoria(int endereco)
{
    if (!cache.empty() && cache.front() == endereco)
    {
        cout << "Cache HIT no endereço: " << endereco << endl;
        return memoria[endereco];
    }

    if (cache.size() == TAMANHO_CACHE)
    {
        cache.pop();
    }

    cache.push(endereco);
    cout << "Cache MISS, carregando endereço: " << endereco << endl;

    return memoria[endereco];
}
