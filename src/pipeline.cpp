#include "pipeline.h"
#include <iostream>

using namespace std;

Pipeline::Pipeline() {
    _instrucaoAtual.assign("");
    _path.assign("instructions.txt");
    _opcode.assign("");
    _reg1 = _reg2 = _regDest = 0;
}

// Etapa de busca
void Pipeline::InstructionFetch() {
    // _instrucaoAtual = instrucao;
    cout << "\n--------- Pipeline Stage: Instruction Fetch ---------\n";
    cout << "Buscando instrucoes..." << endl;

    ifstream instrFile(_path);
    string linha;

    if (instrFile.is_open()) {
        while (getline(instrFile, linha)) {
            _instrucoes.push(linha);
        }
    } else {
        cerr << "Erro ao abrir o arquivo de instruções." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Instrucoes carregadas!" << endl;

    while (!_instrucoes.empty()) {
        auto instrucao = _instrucoes.front();
        _instrucaoAtual.assign(instrucao);
        InstructionDecode();
        _instrucoes.pop();
    }

}

vector<string> Pipeline::tokenizar(string &instrucao) {
    char del = ' ';

    stringstream sstream(instrucao);
    string token;
    vector<string>tokens;

    while (getline(sstream, token, del))
        tokens.push_back(token);

    return tokens;
}

// Função para converter o nome do registrador (ex: R1, R2) para o índice numérico (ex: 1, 2)
int obterIndiceRegistrador(const string &reg) {
    if (reg[0] == 'R') {
        return stoi(reg.substr(1)); // Converte o número após 'R' em um inteiro
    }
    cerr << "Erro: Registrador inválido " << reg << endl;
    exit(EXIT_FAILURE);
}

// Etapa de decodificação
void Pipeline::InstructionDecode() {
    cout << "\n--------- Pipeline Stage: Instruction Decode ---------\n";

    auto tokens = tokenizar(_instrucaoAtual);
    _opcode = tokens[0];

    if (_opcode.compare("LOAD") == 0) {
        _reg1 = obterIndiceRegistrador(tokens[1]);
        auto valor = stoi(tokens[2]);
        _cpu.escreverRegistrador(_reg1, valor);
    } else if (_opcode.compare("STORE") == 0) { 

    } else if (_opcode.compare("IF") == 0) {
        _reg1 = obterIndiceRegistrador(tokens[1]);
        _reg2 = obterIndiceRegistrador(tokens[3]);

        if (tokens[2].compare("<") == 0) {
            UC(4);
        } else if (tokens[2].compare(">") == 0) {
            UC(5);
        } else if (tokens[2].compare("=") == 0) {
            UC(6);
        }
    } else {
        _regDest = obterIndiceRegistrador(tokens[1]);
        _reg1 = obterIndiceRegistrador(tokens[2]);
        _reg2 = obterIndiceRegistrador(tokens[3]);

        if (_opcode.compare("ADD") == 0) {
            UC(0);
        } else if (_opcode.compare("SUB") == 0) {
            UC(1);
        } else if (_opcode.compare("MULT") == 0) {
            UC(2);
        } else if (_opcode.compare("DIV") == 0) {
            UC(3);
        } else {
            cerr << "Erro opcode nao encontrado." << endl;
            exit(EXIT_FAILURE);
        }
    }
}

// Unidade de Controle
void Pipeline::UC(int opcode) {
    int valor1 = _cpu.lerRegistrador(_reg1);
    int valor2 = _cpu.lerRegistrador(_reg2);
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

    _cpu.escreverRegistrador(_regDest, res);
}

// Etapa de execução
int Pipeline::ULA(int var1, int var2, char operador) {
    int resultado;

    cout << "\n--------- Pipeline Stage: Execution ---------\n";

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
            cerr << "[EX] Erro: Divisão por zero!" << endl;
            exit(EXIT_FAILURE);
        }
    case '<':
        return var1 < var2;
    case '>':
        return var1 > var2;
    case '=':
        return var1 == var2;
    default:
        cerr << "[EX] Operacao invalida!" << endl;
        exit(EXIT_FAILURE);
    }
}
