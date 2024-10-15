#ifndef PIPELINE_H
#define PIPELINE_H

void InstructionFetch(int &PC);
void InstructionDecode();
void Execute(int operando1, int operando2);
void MemoryAccess(int endereco);
void WriteBack();

#endif
