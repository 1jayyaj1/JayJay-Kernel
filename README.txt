TO COMPILE AND RUN THE CODE:
1) gcc -c shell.c interpreter.c shellmemory.c cpu.c kernel.c pcb.c ram.c
2) gcc -o mykernel shell.o interpreter.o shellmemory.o cpu.o kernel.o pcb.o ram.o
3) ./mykernel

RULES:
-Please make sure to always add an extra empty trailing line in EACH of the txt files. My code ASSUMES that this is the case.
-Regarding errors, the assignment document is EXTREMELY unclear, and Piazza was full of contradicting messages,
 therefore, here are MY assumptions on the errors based on the assignment doc:
 i)When running exec, if one of the scripts does not exist, then the WHOLE exec command is cancelled. (ram is cleared and exec aborted)
 ii)When running exec, if there are duplicates of scripts, then the WHOLE exec command is cancelled. (ram is cleared and exec aborted)
 iii)When running exec, if one of the scripts makes the ram go over the limit, then the WHOLE exec command is cancelled. (ram is cleared and exec aborted)