#include "../include/pipeline.h"
#include <queue>

// Estrutura para representar uma instrução no pipeline
struct Instrucao {
    std::string instrucaoCompleta;
    std::string opcode;
    int regDest, reg1, reg2;
    int enderecoMemoria;
    int resultado;
    bool memoriaEscrita;

    Instrucao() : regDest(-1), reg1(-1), reg2(-1), enderecoMemoria(-1), resultado(0), memoriaEscrita(false) {}
};

// Filas para os estágios do pipeline
std::queue<Instrucao> IFQueue, IDQueue, EXQueue, MEMQueue, WBQueue;

Pipeline::Pipeline(MemoryRAM &memory, CPU &cpu) {
    _memoryRAM = memory;
    _cpu = cpu;
    _clock = 0;
    _instrucoesFinalizadas = 0;

    executarPipeline();
}

void Pipeline::executarPipeline() {
    const int TAM_I = _memoryRAM.getSize();

    while (_instrucoesFinalizadas < TAM_I) {
        _clock++;
        
        // Avançar instruções entre estágios
        WriteBack();
        MemoryAccess();
        Execute();
        InstructionDecode();
        InstructionFetch();

        // Exibir estado do pipeline para debug
        exibirEstado();
    }
}

void Pipeline::InstructionFetch() {
    if (_cpu.getPC() < _memoryRAM.getSize()) {
        Instrucao instrucao;
        instrucao.instrucaoCompleta = _memoryRAM.getInstrucao(_cpu.getPC());
        _cpu.incrementaPC();
        IFQueue.push(instrucao);

        std::cout << "\n[IF] Instrução buscada: " << instrucao.instrucaoCompleta << std::endl;
    }
}

void Pipeline::InstructionDecode() {
    if (!IFQueue.empty()) {
        Instrucao instrucao = IFQueue.front();
        IFQueue.pop();

        auto tokens = tokenizar(instrucao.instrucaoCompleta);
        instrucao.opcode = tokens[0];

        if (instrucao.opcode == "LOAD") {
            instrucao.regDest = obterIndiceRegistrador(tokens[1]);
            instrucao.enderecoMemoria = stoi(tokens[2]);
        } else if (instrucao.opcode == "STORE") {
            instrucao.reg1 = obterIndiceRegistrador(tokens[1]);
            instrucao.enderecoMemoria = stoi(tokens[2]);
        } else {
            instrucao.regDest = obterIndiceRegistrador(tokens[1]);
            instrucao.reg1 = obterIndiceRegistrador(tokens[2]);
            instrucao.reg2 = obterIndiceRegistrador(tokens[3]);
        }

        IDQueue.push(instrucao);
        std::cout << "[ID] Instrução decodificada: " << instrucao.opcode << std::endl;
    }
}

void Pipeline::Execute() {
    if (!IDQueue.empty()) {
        Instrucao instrucao = IDQueue.front();
        IDQueue.pop();

        if (instrucao.opcode == "ADD") {
            instrucao.resultado = _cpu.lerRegistrador(instrucao.reg1) + _cpu.lerRegistrador(instrucao.reg2);
        } else if (instrucao.opcode == "SUB") {
            instrucao.resultado = _cpu.lerRegistrador(instrucao.reg1) - _cpu.lerRegistrador(instrucao.reg2);
        } else if (instrucao.opcode == "LOAD" || instrucao.opcode == "STORE") {
            // Adiar para estágio de MEM
        }

        EXQueue.push(instrucao);
        std::cout << "[EX] Execução completa: " << instrucao.opcode << std::endl;
    }
}

void Pipeline::MemoryAccess() {
    if (!EXQueue.empty()) {
        Instrucao instrucao = EXQueue.front();
        EXQueue.pop();

        if (instrucao.opcode == "LOAD") {
            instrucao.resultado = _memoryRAM.ler(instrucao.enderecoMemoria);
        } else if (instrucao.opcode == "STORE") {
            _memoryRAM.escrever(instrucao.enderecoMemoria, _cpu.lerRegistrador(instrucao.reg1));
            instrucao.memoriaEscrita = true;
        }

        MEMQueue.push(instrucao);
        std::cout << "[MEM] Acesso à memória: " << instrucao.opcode << std::endl;
    }
}

void Pipeline::WriteBack() {
    if (!MEMQueue.empty()) {
        Instrucao instrucao = MEMQueue.front();
        MEMQueue.pop();

        if (instrucao.opcode == "LOAD" || instrucao.opcode == "ADD" || instrucao.opcode == "SUB") {
            _cpu.escreverRegistrador(instrucao.regDest, instrucao.resultado);
        }

        _instrucoesFinalizadas++;
        std::cout << "[WB] Write back completo: " << instrucao.opcode << std::endl;
    }
}

void Pipeline::exibirEstado() {
    std::cout << "\nClock: " << _clock << std::endl;
    std::cout << "IF Queue: " << IFQueue.size() << " | ID Queue: " << IDQueue.size() << " | EX Queue: " << EXQueue.size() << " | MEM Queue: " << MEMQueue.size() << " | WB Queue: " << WBQueue.size() << "\n";
}

// Função auxiliar para tokenizar uma string em instruções
std::vector<std::string> Pipeline::tokenizar(std::string &instrucao) {
    char del = ' ';
    std::stringstream sstream(instrucao);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(sstream, token, del))
        tokens.push_back(token);

    return tokens;
}

int obterIndiceRegistrador(const std::string &reg) {
    if (reg[0] == 'R') {
        return stoi(reg.substr(1));
    }
    std::cerr << "Erro: Registrador inválido " << reg << std::endl;
    exit(EXIT_FAILURE);
}
