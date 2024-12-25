#ifndef UC_H
#define UC_H

#include "ula.h"

class UC {
public:
    UC(ULA &ula) : _ula(ula) {}
    int executar(int opcode, int valor1, int valor2);

private:
    ULA &_ula;
};

#endif
