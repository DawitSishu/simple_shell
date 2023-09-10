#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *line = NULL;
    char **args = NULL;
    ssize_t read;
    size_t len = 0;

    while (1)
    {
        printf(":) ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin))
            {
                putchar('\n');
                break;
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }
        args = parse_input(line);
        if (args[0] != NULL)
        {
            if (is_exit(args[0]))
            {
                free(args);
                break;
            }
            execute_command(args);
        }
        free(args);
    }

    free(line);
    return (0);
}

