#include "main.h"

/**
 * parse_input - Function to parse the input command line.
 * @line: The input command line to be parsed.
 * Return: An array of strings representing the parsed command line.
 */
char **parse_input(char *line)
{
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token)
    {
        tokens[position] = token;
        position++;

        if (position >= buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

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

/**
 * find_command - Function to find the command executable path.
 * @cmd: The command to search for.
 * Return: A string representing the path to the command executable, or NULL if not found.
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
            return cmd_path;
        }

        free(cmd_path);
        token = strtok(NULL, ":");
    }

    return NULL;
}

/**
 * is_exit - Function to check if the command is an exit command.
 * @cmd: The command to check.
 * Return: 1 if the command is an exit command, 0 otherwise.
 */
int is_exit(char *cmd)
{
    return strcmp(cmd, "exit") == 0;
}

