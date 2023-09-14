#include "main.h"
/**
 * is_exit - Function to check if the command is an exit command.
 * @cmd: The command to check.
 * Return: 1 if the command is an exit command, 0 otherwise.
 */
int is_exit(char *cmd)
{
return (strcmp(cmd, "exit") == 0);
}
