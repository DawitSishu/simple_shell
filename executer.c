#include "main.h"

/**
* execute_command - Function to execute a command with given arguments.
* @args: An array of strings representing the command and its arguments.
*/
void execute_command(char **args)
{
pid_t pid;
int status;
char *cmd_path;

cmd_path = find_command(args[0]);
if (cmd_path == NULL)
{
printf("Command not found\n");
return;
}

pid = fork();
if (pid == 0)
{
if (execve(cmd_path, args, environ) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
}
free(cmd_path);
}
