#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "kernel.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"

ReadyQueueNode *createReadyQueueNode() {
    ReadyQueueNode *rqn = malloc(sizeof(ReadyQueueNode));
    rqn->pcb = NULL;
    rqn->next = NULL;
    return rqn;
}

ReadyQueue *createReadyQueue() {
    ReadyQueue *rq = malloc(sizeof(ReadyQueue));
    rq->head = NULL;
    rq->tail = NULL;
    return rq;
}

CPU *createCPU() {
    CPU *cpu = malloc(sizeof(CPU));
    cpu->quanta = 2;
    return cpu;
}

List *l;
ReadyQueue* rq;
CPU* cpu;

void addToReady(PCB* p) {
    ReadyQueueNode* rqn = createReadyQueueNode();
    rqn->pcb = p;
    if (rq->head == NULL && rq->tail == NULL) {
        rq->head = rqn;
        rq->tail = rqn;
    } else {
        rqn->next = rq->tail;
        rq->tail = rqn;
    }
}

int isEmpty() {
    if (rq->head == NULL && rq->tail == NULL) {
        return 1; //List is empty - true
    }
    return -1;  //List is not empty - false
}

 void removePCB() {
    if (rq->head == rq->tail) {
        rq->head = NULL;
        rq->tail = NULL;
    } else {
        ReadyQueueNode* rqn = rq->tail;
        while (rqn->next != rq->head) {
            rqn = rqn->next;
        }
        rqn->next = NULL;
        rq->head = rqn;
    }
}

 ReadyQueueNode* getNext() {
    ReadyQueueNode* temp = rq->head;
    removePCB();
    return temp;
}

void myinit(char* filename) {
    FILE *p = fopen(filename,"rt");
    int start = getNextAvailableIndex();
    int end = 0;
    addToRAM(p, &start, &end);
    PCB* pcb = makePCB(start, end);
    addToReady(pcb);
    // printf("RQ Tail node pcb start: ");
    // printf("%i\n", rq->tail->pcb->start);
    // printf("RQ Tail node pcb end: ");
    // printf("%i\n", rq->tail->pcb->end);
    // printf("RQ Head node pcb start: ");
    // printf("%i\n", rq->head->pcb->start);
    // printf("RQ Head node pcb end: ");
    // printf("%i\n", rq->head->pcb->end);
}

void scheduler() {
    // printf("RQ Tail node pcb start: ");
    // printf("%i\n", rq->tail->pcb->start);
    // printf("RQ Tail node pcb end: ");
    // printf("%i\n", rq->tail->pcb->end);
    // printf("RQ Head node pcb start: ");
    // printf("%i\n", rq->head->pcb->start);
    // printf("RQ Head node pcb end: ");
    // printf("%i\n", rq->head->pcb->end);
    //Currently implementing
    cpu = createCPU();
    ReadyQueueNode* temp;
    while (isEmpty() == -1) {
        temp = getNext();
        cpu->IP = temp->pcb->PC;
        //printf("This is the start cpu->IP: %i\n",cpu->IP);
        if ((temp->pcb->PC)+2 > temp->pcb->end) {
            cpu->quanta = 1;
        }
        run(cpu, l);
        temp->pcb->PC = (cpu->IP) + 1;
        //printf("This is the end cpu->IP: %i\n",temp->pcb->PC);
        if (cpu->IP != temp->pcb->end) {
            addToReady(temp->pcb);
        }
    }
    //printf("Ready queue is empty\n");
}

int main() {
    char userInput[1000];
    char prompt[100] = {'$', '\0'};
    l = List_create();
    rq = createReadyQueue();
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