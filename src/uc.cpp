#include "uc.h"
#include <iostream>

int UC::executar(int opcode, int valor1, int valor2) {
    switch (opcode) {
    case 0: return _ula.executar(valor1, valor2, '+');
    case 1: return _ula.executar(valor1, valor2, '-');
    case 2: return _ula.executar(valor1, valor2, '*');
    case 3: return _ula.executar(valor1, valor2, '/');
    default:
        std::cerr << "Opcode inválido!" << std::endl;
        exit(EXIT_FAILURE);
    }
}
