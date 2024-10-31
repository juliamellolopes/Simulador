#ifndef PIPELINE_H
#define PIPELINE_H

#include <fstream>
#include <sstream>
#include <queue>
#include "cpu.h"

#define DBG(x) std::cerr << #x << " = " << (x) <<std::endl;

class Pipeline {
public:
    Pipeline();
    void InstructionFetch();
    void InstructionDecode();
    int ULA(int var1, int var2, char var3);        // Unidade logica aritimetica  
    void UC(int opcode);                           // Unidade de controle 
    vector<string>tokenizar(string &instrucao);

private:
    queue<string>_instrucoes;
    string _instrucaoAtual;
    string _opcode;
    int _reg1, _reg2, _regDest;
    CPU _cpu;
    string _path;
};

#endif
