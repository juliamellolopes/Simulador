#ifndef UC_H
#define UC_H

#include "ula.h"

class UC {
private:
    ULA &_ula;

public:
    UC(ULA &ula) : _ula(ula) {}
    int executar(int opcode, int valor1, int valor2);
};

#endif
