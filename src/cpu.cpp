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

int CPU::getPC() {
    return _PC;
}

int CPU::lerRegistrador(int reg) {
    return _cores[_coreAtivo]._registradores[reg - 1];
}

void CPU::escreverRegistrador(int reg, int valor) {
    _cores[_coreAtivo]._registradores[reg - 1] = valor;
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
