#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "shellmemory.h"
#include "kernel.h"

void interpret(char* parsedInput, List *l);

// char** parse(char userInput[]) {
//     char ** parsedUserInput = malloc(100 * sizeof(char*));
//     for (int i = 0 ; i < 100; ++i) {
//         parsedUserInput[i] = malloc(100 * sizeof(char));
//     }
//     char tmp[200];
//     int a,b;
//     int w=0;
//     for(a=0; userInput[a]==' ' && a<100; a++);
//     while(userInput[a] != '\0' && a<100) {
//         for(b=0; userInput[a]!='\0' && userInput[a]!=' ' && a<1000; a++, b++)
//             tmp[b] = userInput[a];
//         tmp[b] = '\0';
//         parsedUserInput[w] = strdup(tmp);
//         a++; w++;
//     }
//     return parsedUserInput;
// }

int getSize(char* str){
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    return (int)num_tokens;
}

char **parse(char *str)
{
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    char **ret_arr =
        (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;
    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }
    return ret_arr;
}

void help(int num_tokens) {
    if (num_tokens != 1) {
        printf("Use the command “help” to view the available commands.\n");
    } else {
        printf("COMMANDS:\n");
        printf("help: Displays all the commands\n");
        printf("quit: Exits/terminates the shell with “Bye!”\n");
        printf("set VAR STRING: Assigns a value to shell memory\n");
        printf("print VAR: Displays the STRING assigned to VAR\n");
        printf("run SCRIPT.txt: Executes the file SCRIPT.TXT\n");
    }
}

void setVar(char** parsedInput, int num_tokens, List *l) {
    if (num_tokens < 3) {
        printf("Please use this format to set a variable: set VAR STRING\n");
    } else {
        char *var = List_find(l, strdup(parsedInput[1]));
        if (strcmp(var, "Variable does not exist") == 0) {
            List_append(l, strdup(parsedInput[1]), strdup(parsedInput[2]));
        } else {
            List_update(l, strdup(parsedInput[1]), strdup(parsedInput[2]));
        }
    }   
}

void printVar(char** parsedInput, int num_tokens, List *l) {
    if (num_tokens != 2) {
        printf("Please use this format to print a variable: print VAR\n");
    } else {
        printf("%s\n", List_find(l, strdup(parsedInput[1])));
    }
}

int runFile(char** parsedInput, int num_tokens, List *l) {
    if (num_tokens > 4 || num_tokens < 2) {
        printf("Please use this format to run a text file: run SCRIPT.txt\n");
    } else {
        int errCode = 0;
        char line[1000];
        FILE *p = fopen(parsedInput[1],"rt");
        if (p==NULL){
            printf("Script not found\n");
            return 0;
        }
        fgets(line,999,p);
        while(!feof(p)) {
            interpret(line, l);
            if (errCode != 0) {
                fclose(p);
            }
            fgets(line,999,p);
            // printf("%s", line);
        }
        fclose(p);
        return 0;
    }
    return 0;
}

int exec(char** parsedInput, int num_tokens, List *l) {
    if (num_tokens > 4 || num_tokens < 2) {
        printf("Please use this format to execute programs: exec prog1.txt prog2.txt prog3.txt\n");
    } else {
        for (int i = 1; i < num_tokens; i++) {
            myinit(parsedInput[i]);
        }
        scheduler();
    }
    return 0;
}

int quit(int num_tokens) {
    if (num_tokens != 1) {
        printf("Use the command “quit” to quit the program.\n");
    } else {
        printf("Bye!\n");
        exit(0);
    }
    return 0;
}

void interpret(char* parsedInput, List *l) {
    int num_tokens = getSize(parsedInput);
    char **tokens = parse(parsedInput);
    if (strcmp(tokens[0], "help") == 0) {
        help(num_tokens);
    } else if (strcmp(tokens[0], "set") == 0) {
        setVar(tokens,num_tokens,l);
    } else if (strcmp(tokens[0], "print") == 0) {
        printVar(tokens,num_tokens,l);
    } else if (strcmp(tokens[0], "run") == 0) {
        runFile(tokens,num_tokens,l);
    } else if (strcmp(tokens[0], "exec") == 0) {
        exec(tokens,num_tokens,l);
    } else if (strcmp(tokens[0], "quit") == 0) {
        quit(num_tokens);
    } else {
        if (strcmp(tokens[0], "") != 0) {
            printf("Unknown command\n");
        }
    }
}
