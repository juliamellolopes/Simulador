#ifndef PCB_H
#define PCB_H

#include <vector>
#include <string>

#define DEFAULT_QUANTUM 4
#define TAM_R 16

class PCB {
public:
    int id;
    std::string estado;
    int prioridade;
    int quantumRestante;
    std::vector<int> registradores;

    PCB(int id, int prioridade)
        : id(id), prioridade(prioridade), quantumRestante(DEFAULT_QUANTUM) {
        estado = "pronto";
        registradores = std::vector<int>(TAM_R, 0);
    }
};

#endif
