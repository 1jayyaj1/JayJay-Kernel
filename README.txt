This assignment was done using mimi.mcgill. The only "special" instruction is that you add a new line (press enter) at the end of the testfile.txt. To start the shell, run these commands in the following sequence:

1) gcc -c shell.c interpreter.c shellmemory.c
2) gcc -o mysh shell.o interpreter.o shellmemory.o
3) ./mysh