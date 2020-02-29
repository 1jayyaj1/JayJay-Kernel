#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

void shellUI(List* l) {
    char prompt[100] = {'$', '\0'};
    printf("Kernel 1.0 loaded!\n");
    printf("Welcome to the JayJay shell!\n");
    printf("Shell version 2.0 Updated February 2020\n");
    while(!feof(stdin)) {
        printf("%s ", prompt);
        fflush(stdout);
        char *line = NULL;
        size_t linecap = 0;
        if (getline(&line, &linecap, stdin) == -1)
            break;
        (void)interpret(line,l);
        free(line);
	}
}
