#include "ula.h"
#include <iostream>

int ULA::executar(int var1, int var2, char operador) {
    switch (operador) {
    case '+': return var1 + var2;
    case '-': return var1 - var2;
    case '*': return var1 * var2;
    case '/': 
        if (var2 != 0) return var1 / var2;
        std::cerr << "Erro: Divisão por zero!" << std::endl;
        exit(EXIT_FAILURE);
    default:
        std::cerr << "Operação inválida!" << std::endl;
        exit(EXIT_FAILURE);
    }
}
