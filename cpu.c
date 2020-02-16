#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "ram.h"
#include "interpreter.h"

void run(CPU* cpu, List *l) {
    for (int i = 0; i < cpu->quanta; i++) {
        cpu->IP = (cpu->IP) + i;
        interpret(parse(getInstruction(cpu->IP)), l);
        //printf("%s\n", getInstruction(cpu->IP));
    }
}