#include "../include/cpu.h"

REG::REG() {
    _registradores = vector(TAM_R, 0);
}

// Construtor da CPU com número de cores
CPU::CPU(MemoryRAM &memory) {
    _memoryRAM = memory;
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<REG>(TAM_C);
    cout << "--- Iniciando Simulacao com " << TAM_C << " Cores e " << TAM_R << " Registradores cada ---" << endl;

    // _pipeline.InstructionFetch();
    // loop();
}

int CPU::getPC() {
    return _PC;
}

void CPU::incrementaPC() {
    _PC++;
    _PC = _PC % _memoryRAM.getSize();
}

// // Alternar para um core específico
// void CPU::alternarCore(int coreId) {
//     if (coreId >= 0 && coreId < numCoresAtivos) {
//         coreAtivo = coreId;
//         cout << "--- Core " << coreAtivo << " Ativo ---" << endl;
//     } else {
//         cerr << "Erro: Core inválido!" << endl;
//     }
// }

// Lê o valor de um registrador
int CPU::lerRegistrador(int reg) {
    if (reg > 0 && reg <= TAM_R) {
        // cout << "Lendo valor do Registrador R" << reg << " no Core " << coreAtivo << ": " << registradores[coreAtivo][reg] << endl;
        return _cores[_coreAtivo]._registradores[reg - 1];
    } else {
        cerr << "Erro: Registrador invalido!" << endl;
        return -1;
    }

    // return 2;
}

// Escreve um valor em um registrador
void CPU::escreverRegistrador(int reg, int valor) {
    if (reg > 0 && reg <= TAM_R) {
        _cores[_coreAtivo]._registradores[reg - 1] = valor;
        cout << "Valor " << valor << " foi escrito no Registrador R" << reg << " no Core " << _coreAtivo << endl;
    } else {
        cerr << "Erro: Registrador invalido!" << endl;
    }
}

// Escreve um valor em um endereço de memória
void CPU::escreverNaMemoria(int endereco) {
    int valor = lerRegistrador(_reg1);
    _memoryCache.escrever(endereco, valor);
}

// // Lê um valor de um endereço de memória
// int CPU::lerDaMemoria(int endereco) {
//     if (memoria.find(endereco) != memoria.end()) {
//         cout << "Lendo valor do endereco " << endereco << ": " << memoria[endereco] << endl;
//         return memoria[endereco];
//     } else {
//         cerr << "Erro: Endereco de memoria nao encontrado!" << endl;
//         return -1;
//     }
// }

// // Exibe o estado de registradores relevantes
// void CPU::mostrarEstadoRegistradores(int reg1, int reg2, int regDest) {
//     // cout << "Estado atualizado dos registradores no Core " << coreAtivo << ":\n";
//     // cout << "R" << reg1 << ": " << registradores[coreAtivo][reg1] << endl;
//     // cout << "R" << reg2 << ": " << registradores[coreAtivo][reg2] << endl;
//     // cout << "R" << regDest << ": " << registradores[coreAtivo][regDest] << endl;
// }

// Unidade de Controle
void CPU::UC(int opcode) {
    int valor1 = lerRegistrador(_reg1);
    int valor2 = lerRegistrador(_reg2);
    int res;

    switch (opcode) {
    case 0:
        res = ULA(valor1, valor2, '+');
        cout << "Executando operacao ADD: " << valor1 << " + " << valor2 << " = " << res << endl;
        break;
    case 1:
        res = ULA(valor1, valor2, '-');
        cout << "Executando operacao SUB: " << valor1 << " - " << valor2 << " = " << res << endl;
        break;
    case 2:
        res = ULA(valor1, valor2, '*');
        cout << "Executando operacao MULT: " << valor1 << " * " << valor2 << " = " << res << endl;
        break;
    case 3:
        res = ULA(valor1, valor2, '/');
        cout << "Executando operacao DIV: " << valor1 << " / " << valor2 << " = " << res << endl;
        break;
    case 4:
        res = ULA(valor1, valor2, '<');
        cout << "Executando operacao IF: " << valor1 << " < " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    case 5:
        res = ULA(valor1, valor2, '>');
        cout << "Executando operacao IF: " << valor1 << " > " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    case 6:
        res = ULA(valor1, valor2, '=');
        cout << "Executando operacao IF: " << valor1 << " == " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    default:
        res = 0;
        break;
    }

    escreverRegistrador(_regDest, res);
}

// Etapa de execução
int CPU::ULA(int var1, int var2, char operador) {
    int resultado;

    cout << "\n--------- CPU: Unidade Lógica Aritmética ---------\n";

    switch (operador) {
    case '+': // ADD
        return var1 + var2;
    case '-': // SUB
        return var1 - var2;
    case '*': // MULT
        return var1 * var2;
    case '/': // DIV
        if (var2 != 0) {
            return var1 / var2;
        } else {
            cerr << "Erro: Divisão por zero!" << endl;
            exit(EXIT_FAILURE);
        }
    case '<':
        return var1 < var2;
    case '>':
        return var1 > var2;
    case '=':
        return var1 == var2;
    default:
        cerr << "Operacao invalida!" << endl;
        exit(EXIT_FAILURE);
    }
}