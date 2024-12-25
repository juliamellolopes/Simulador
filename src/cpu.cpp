#include "cpu.h"
#include <iostream>

using namespace std;

// Construtor da classe REG
REG::REG() {
    _registradores = vector<int>(TAM_R, 0); // Inicializa registradores com zeros
}

// Construtor da CPU
CPU::CPU(MemoryRAM &memory) : _ula(), _uc(_ula) {
    _memoryRAM = memory;
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<REG>(TAM_C); // Inicializa núcleos
    cout << "--- Iniciando Simulação com " << TAM_C << " Cores e " << TAM_R << " Registradores cada ---" << endl;
}

// Incrementa o contador de programa
void CPU::incrementarPC() {
    _PC++;
    _PC = _PC % _memoryRAM.getSize(); // Faz loop no tamanho da memória
}

// Retorna o valor do contador de programa
int CPU::getPC() {
    return _PC;
}

// Lê o valor de um registrador específico do núcleo ativo
int CPU::lerRegistrador(int reg) {
    if (reg > 0 && reg <= TAM_R) {
        return _cores[_coreAtivo]._registradores[reg - 1];
    } else {
        cerr << "Erro: Registrador inválido!" << endl;
        return -1;
    }
}

// Escreve um valor em um registrador específico do núcleo ativo
void CPU::escreverRegistrador(int reg, int valor) {
    if (reg > 0 && reg <= TAM_R) {
        _cores[_coreAtivo]._registradores[reg - 1] = valor;
        cout << "Valor " << valor << " foi escrito no Registrador R" << reg << " no Core " << _coreAtivo << endl;
    } else {
        cerr << "Erro: Registrador inválido!" << endl;
    }
}

// Executa uma instrução baseada no opcode
void CPU::executarInstrucao(int opcode) {
    int valor1 = lerRegistrador(1); // Exemplo: registrador 1
    int valor2 = lerRegistrador(2); // Exemplo: registrador 2
    int resultado = _uc.executar(opcode, valor1, valor2);
    escreverRegistrador(3, resultado); // Escreve o resultado no registrador 3
}
