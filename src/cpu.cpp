#include "cpu.h"
#include <iostream>

using namespace std;

// Construtor da classe REG
REG::REG() {
    _registradores = vector<int>(TAM_R, 0);
}

// Construtor da CPU
CPU::CPU(MemoryRAM &memory) : _ula(), _uc(_ula), _memoryRAM(memory) {
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<REG>(4);
    processoAtual = nullptr;
    cout << "--- Iniciando Simulação ---" << endl;
}

void CPU::incrementarPC() {
    _PC++;
    _PC = _PC % _memoryRAM.getSize();
}

// cpu.cpp
int CPU::lerRegistrador(int index) {
    return _registradores[index];
}

void CPU::escreverRegistrador(int index, int valor) {
    _registradores[index] = valor;
}

void CPU::setPC(int novoPC) {
    _PC = novoPC;
}

int CPU::getPC() {
    return _PC;
}

void CPU::carregarProcesso(PCB *pcb) {
    processoAtual = pcb;
    processoAtual->estado = "executando";
}

void CPU::salvarEstadoAtual() {
    if (processoAtual) {
        processoAtual->estado = "pronto";
        filaProntos.push(processoAtual);
        processoAtual = nullptr;
    }
}

void CPU::adicionarProcesso(PCB *pcb) {
    filaProntos.push(pcb);
}

void CPU::executar() {
    while (!filaProntos.empty()) {
        if (!processoAtual) {
            carregarProcesso(filaProntos.front());
            filaProntos.pop();
        }

        processoAtual->quantumRestante--;

        if (processoAtual->quantumRestante == 0) {
            salvarEstadoAtual();
        }
    }
}
