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
    //CURRENTLY IMPLEMENTING
    FILE *p = fopen(filename,"rt");
    int start = getNextAvailableIndex();
    int end = 0;
    addToRAM(p, &start, &end);
    PCB* pcb = makePCB(start, end);
    addToReady(pcb);
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