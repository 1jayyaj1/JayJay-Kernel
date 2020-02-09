gcc -c shell.c interpreter.c shellmemory.c cpu.c kernel.c pcb.c ram.c
gcc -o mykernel shell.o interpreter.o shellmemory.o cpu.o kernel.o pcb.o ram.o