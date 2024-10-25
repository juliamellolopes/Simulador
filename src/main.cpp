#include <iostream>
#include <fstream>
#include <sstream>
#include "cpu.h"
#include "pipeline.h"
#include "memory.h"

using namespace std;

// Função para converter o nome do registrador (ex: R1, R2) para o índice numérico (ex: 1, 2)
int obterIndiceRegistrador(const string &reg)
{
    if (reg[0] == 'R')
    {
        return stoi(reg.substr(1)); // Converte o número após 'R' em um inteiro
    }
    cerr << "Erro: Registrador inválido " << reg << endl;
    return -1;
}

// Função para lidar com operações inválidas e executar as válidas
void pipelineExecutaInstrucao(int opcode, CPU &cpu, Pipeline &pipeline)
{
    switch (opcode)
    {
    case 0: // LOAD
    case 1: // ADD
    case 2: // SUB
    case 3: // MULT
    case 4: // DIV
    case 5: // STORE
        pipeline.Execute();
        break;
    default:
        std::cerr << "[EX] Operacao invalida! Opcode: " << opcode << std::endl;
        break;
    }
}

// Função para executar as instruções carregadas do arquivo
void executarInstrucoes(CPU &cpu, Pipeline &pipeline, Memory &memory, const string &arquivo)
{
    ifstream instrFile(arquivo);
    string linha;

    if (!instrFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo de instruções." << endl;
        return;
    }

    while (getline(instrFile, linha))
    {
        istringstream iss(linha);
        string instrucao;
        iss >> instrucao;

        if (instrucao == "LOAD")
        {
            string reg;
            int valor;
            iss >> reg >> valor;
            int regNum = obterIndiceRegistrador(reg);
            cpu.escreverRegistrador(regNum, valor);
            cout << "Carregando valor " << valor << " no " << reg << endl;
            pipeline.InstructionFetch(0);
            pipeline.InstructionDecode();
            pipelineExecutaInstrucao(0, cpu, pipeline);
        }
        else if (instrucao == "ADD")
        {
            string reg1, reg2, regDest;
            iss >> reg1 >> reg2 >> regDest;
            int reg1Num = obterIndiceRegistrador(reg1);
            int reg2Num = obterIndiceRegistrador(reg2);
            int regDestNum = obterIndiceRegistrador(regDest);

            int valor1 = cpu.lerRegistrador(reg1Num);
            int valor2 = cpu.lerRegistrador(reg2Num);
            int resultado = valor1 + valor2;

            cout << "Executando ADD: " << valor1 << " + " << valor2 << " = " << resultado << endl;
            cpu.escreverRegistrador(regDestNum, resultado);
            pipeline.InstructionFetch(1);
            pipeline.InstructionDecode();
            pipelineExecutaInstrucao(1, cpu, pipeline);
        }
        else if (instrucao == "SUB")
        {
            string reg1, reg2, regDest;
            iss >> reg1 >> reg2 >> regDest;
            int reg1Num = obterIndiceRegistrador(reg1);
            int reg2Num = obterIndiceRegistrador(reg2);
            int regDestNum = obterIndiceRegistrador(regDest);

            int valor1 = cpu.lerRegistrador(reg1Num);
            int valor2 = cpu.lerRegistrador(reg2Num);
            int resultado = valor1 - valor2;

            cout << "Executando SUB: " << valor1 << " - " << valor2 << " = " << resultado << endl;
            cpu.escreverRegistrador(regDestNum, resultado);
            pipeline.InstructionFetch(2);
            pipeline.InstructionDecode();
            pipelineExecutaInstrucao(2, cpu, pipeline);
        }
        else if (instrucao == "MULT")
        {
            string reg1, reg2, regDest;
            iss >> reg1 >> reg2 >> regDest;
            int reg1Num = obterIndiceRegistrador(reg1);
            int reg2Num = obterIndiceRegistrador(reg2);
            int regDestNum = obterIndiceRegistrador(regDest);

            int valor1 = cpu.lerRegistrador(reg1Num);
            int valor2 = cpu.lerRegistrador(reg2Num);
            int resultado = valor1 * valor2;

            cout << "Executando MULT: " << valor1 << " * " << valor2 << " = " << resultado << endl;
            cpu.escreverRegistrador(regDestNum, resultado);
            pipeline.InstructionFetch(3);
            pipeline.InstructionDecode();
            pipelineExecutaInstrucao(3, cpu, pipeline);
        }
        else if (instrucao == "DIV")
        {
            string reg1, reg2, regDest;
            iss >> reg1 >> reg2 >> regDest;
            int reg1Num = obterIndiceRegistrador(reg1);
            int reg2Num = obterIndiceRegistrador(reg2);
            int regDestNum = obterIndiceRegistrador(regDest);

            int valor1 = cpu.lerRegistrador(reg1Num);
            int valor2 = cpu.lerRegistrador(reg2Num);

            if (valor2 != 0)
            {
                int resultado = valor1 / valor2;
                cout << "Executando DIV: " << valor1 << " / " << valor2 << " = " << resultado << endl;
                cpu.escreverRegistrador(regDestNum, resultado);
            }
            else
            {
                cout << "Erro: Divisao por zero." << endl;
            }

            pipeline.InstructionFetch(4);
            pipeline.InstructionDecode();
            pipelineExecutaInstrucao(4, cpu, pipeline);
        }
        else if (instrucao == "STORE")
        {
            string reg;
            int endereco;
            iss >> reg >> endereco;
            int regNum = obterIndiceRegistrador(reg);
            int valor = cpu.lerRegistrador(regNum);

            memory.escrever(endereco, valor);
            cout << "Armazenando valor " << valor << " do " << reg << " no endereço " << endereco << endl;

            pipeline.InstructionFetch(5);
            pipeline.InstructionDecode();
            pipelineExecutaInstrucao(5, cpu, pipeline);
        }
        else if (instrucao == "IF")
        {
            string reg1, op, reg2;
            iss >> reg1 >> op >> reg2;
            int reg1Num = obterIndiceRegistrador(reg1);
            int reg2Num = obterIndiceRegistrador(reg2);

            int valor1 = cpu.lerRegistrador(reg1Num);
            int valor2 = cpu.lerRegistrador(reg2Num);
            bool condicao = false;

            if (op == ">")
                condicao = (valor1 > valor2);
            else if (op == "<")
                condicao = (valor1 < valor2);
            else if (op == "==")
                condicao = (valor1 == valor2);
            else if (op == "!=")
                condicao = (valor1 != valor2);

            if (condicao)
            {
                cout << "Condição IF " << reg1 << " " << op << " " << reg2 << " satisfeita." << endl;
            }
            else
            {
                cout << "Condição IF " << reg1 << " " << op << " " << reg2 << " não satisfeita." << endl;
            }
        }
    }
}

int main()
{
    // Inicializa a CPU com 4 cores, o pipeline e a memória
    CPU cpu(2);
    Pipeline pipeline(cpu);
    Memory memory;

    // Executa as instruções carregadas do arquivo
    executarInstrucoes(cpu, pipeline, memory, "instructions.txt");

    return 0;
}
