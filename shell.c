#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

void shellUI(List* l) {
    char userInput[1000];
    char prompt[100] = {'$', '\0'};
    printf("Kernel 1.0 loaded!\n");
    printf("Welcome to the JayJay shell!\n");
    printf("Shell version 2.0 Updated February 2020\n");
    int leaveStatus = 0;
    do {
        int size;
        printf("%s ", prompt);
        fgets(userInput,999,stdin);
        size = strlen(userInput);
        userInput[size-1]='\0';
        leaveStatus = interpret(parse(userInput),l);
	}
	while(leaveStatus == 0);
	printf("Bye!\n");
}