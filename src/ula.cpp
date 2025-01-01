#include "ula.h"
#include <iostream>

int ULA::executarOperacao(int operando1, int operando2, string operacao) {
    if (operacao == "ADD") return operando1 + operando2;
    if (operacao == "SUB") return operando1 - operando2;
    if (operacao == "AND") return operando1 & operando2;
    if (operacao == "OR") return operando1 | operando2;
    cerr << "Operação inválida: " << operacao << endl;
    exit(EXIT_FAILURE);
}
