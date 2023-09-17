#include "main.h"

/**
 * find_command - Function to find the command executable path.
 * @cmd: The command to search for.
 * Return: A string representing the path to the command.
 */
char *find_command(char *cmd)
{
char *path = getenv("PATH");
char *dir;
char *cmd_path;
char *token;
struct stat st;

token = strtok(path, ":");
while (token)
{
dir = token;
cmd_path = malloc(strlen(dir) + strlen(cmd) + 2);
if (!cmd_path)
{
perror("malloc");
exit(EXIT_FAILURE);
}
sprintf(cmd_path, "%s/%s", dir, cmd);

if (stat(cmd_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
return (cmd_path);
}

free(cmd_path);
token = strtok(NULL, ":");
}

return (NULL);
}
