#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

extern char **environ;

char **parse_input(char *line);
void execute_command(char **args);
char *find_command(char *cmd);
int is_exit(char *cmd);

#endif /* MAIN_H */

