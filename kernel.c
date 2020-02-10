#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "ram.h"
#include "pcb.h"

List *l;
void addToReady(PCB* p);

void myinit(char* filename) {
    //TO IMPLEMENT
    printf("Function myinit still needs to be implemented.\n");
    // addToRAM(file, start, end);
    PCB* demo = makePCB(1,2);
    printf("Created demo PCB with PC value: %d\n", demo->PC);
    printf("Created demo PCB with start value: %d\n", demo->start);
    printf("Created demo PCB with end value: %d\n", demo->end);
    addToReady(demo);
}

void scheduler() {
    //TO IMPLEMENT
    printf("Function scheduler still needs to be implemented.\n");
}

void addToReady(PCB* p) {
    //TO IMPLEMENT
    printf("Function addToReady still needs to be implemented.\n");
}

int main() {
    char userInput[1000];
    char prompt[100] = {'$', '\0'};
    l = List_create();
    printf("Welcome to the JayJay shell!\n");
    printf("Version 1.0 Created January 2020\n");
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