#include <iostream>
// #include <fstream>
// #include <sstream>
// #include "cpu.h"
#include "../include/pipeline.h"
// #include "../include/memory.h"
// #include "../include/cpu.h"

using namespace std;


int main() {
    MemoryRAM memory("instructions.txt");
    CPU cpu(memory);
    Pipeline pipeline(memory, cpu);

    return 0;
}
