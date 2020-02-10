typedef struct CPU {
    int IP;
    char IR[1000];
    int quanta=2;
} CPU;