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
tokens = realloc(tokens, buffer_size *sizeof(char *));
if (!tokens)
{
perror("realloc");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, " \t\r\n\a");
}
tokens[position] = NULL;
return (tokens);
}
