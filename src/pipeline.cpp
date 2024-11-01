#include "../include/pipeline.h"

vector<string> Pipeline::tokenizar(string &instrucao) {
    char del = ' ';

    stringstream sstream(instrucao);
    string token;
    vector<string>tokens;

    while (getline(sstream, token, del))
        tokens.push_back(token);

    return tokens;
}

Pipeline::Pipeline(MemoryRAM &memory, CPU &cpu) {
    _memoryRAM = memory;
    _cpu = cpu;
    _instrucaoAtual.assign("");
    _opcode.assign("");
    _cpu._reg1 = _cpu._reg2 = _cpu._regDest = 0;

    loop();
}

void Pipeline::loop() {
    const int TAM_I = _memoryRAM.getSize();   // tamanho de instruções 
    vector<bool> control(TAM_I, false);    // variavel de controle da utilização da instrução (true - usado, false - não usado)
    int cont = TAM_I;

    while (cont > 0) {
        if (control[_cpu.getPC()] == false) {
            cont = TAM_I;
            control[_cpu.getPC()] = true;
            InstructionFetch();
        } else {
            cont--;
        }
    }
}

// Etapa de busca
void Pipeline::InstructionFetch() {
    cout << "\n--------- Pipeline Stage: Instruction Fetch ---------\n";
    cout << "Buscando instrucao..." << endl;
    _instrucaoAtual.assign(_memoryRAM.getInstrucao(_cpu.getPC()));

    InstructionDecode();

    _cpu.incrementaPC();
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

    cout << "Decodificand: " << _instrucaoAtual << endl;

    auto tokens = tokenizar(_instrucaoAtual);
    _opcode = tokens[0];

    if (_opcode.compare("LOAD") == 0) {
        _cpu._reg1 = obterIndiceRegistrador(tokens[1]);
        auto valor = stoi(tokens[2]);
        _cpu.escreverRegistrador(_cpu._reg1, valor);
    } else if (_opcode.compare("STORE") == 0) {
        auto endereco = stoi(tokens[2]);
        _cpu._reg1 = obterIndiceRegistrador(tokens[1]);

        _cpu.escreverNaMemoria(endereco);
    } else if (_opcode.compare("IF") == 0) {
        _cpu._reg1 = obterIndiceRegistrador(tokens[1]);
        _cpu._reg2 = obterIndiceRegistrador(tokens[3]);

        Execute(tokens[2]);
    } else {
        _cpu._regDest = obterIndiceRegistrador(tokens[1]);
        _cpu._reg1 = obterIndiceRegistrador(tokens[2]);
        _cpu._reg2 = obterIndiceRegistrador(tokens[3]);

        Execute(_opcode);
    }
}

// Etapa de Execução
void Pipeline::Execute(string code) {
    cout << "\n--------- Pipeline Stage: Execution ---------\n";
    cout << "Chamando operações CPU" << endl;

    if (code.compare("<") == 0) {
        _cpu.UC(4);
    } else if (code.compare(">") == 0) {
        _cpu.UC(5);
    } else if (code.compare("=") == 0) {
        _cpu.UC(6);
    } else if (code.compare("ADD") == 0) {
        _cpu.UC(0);
    } else if (code.compare("SUB") == 0) {
        _cpu.UC(1);
    } else if (code.compare("MULT") == 0) {
        _cpu.UC(2);
    } else if (code.compare("DIV") == 0) {
        _cpu.UC(3);
    } else {
        cerr << "Erro opcode nao encontrado." << endl;
        exit(EXIT_FAILURE);
    }
}