#include "main.h"
/**
* main - main entry function
* @argc: argument variables count
* @argv:  argument variables
*
* Return: 0, success.
*/
int main(int argc, char **argv)
{
char *prompt, *prompt_copy = NULL, *token;
size_t buffer_len = 0;
ssize_t char_no;
const char *delimiter = " \n";
int num_tokens = 0, i;
(void)argc;

while (true)
{
printf("$ ");
/* get the input*/
char_no = getline(&prompt, &buffer_len, stdin);
if (char_no == -1)
{
return (-1);
}
/* copy the found prompt for later use*/
prompt_copy = malloc(sizeof(char) * char_no);
if (prompt_copy == NULL)
{
return (-1);
}
strcpy(prompt_copy, prompt);
/* count the number of tokens by spliting prompt with delimiter*/
token = strtok(prompt, delimiter);
while (token != NULL){
num_tokens++;
token = strtok(NULL, delimiter);
}
num_tokens++;
/* allocate memory for argv to sav the tokens*/
argv = malloc(sizeof(char *) * num_tokens);
if (argv == NULL) {
    return (-1);
}

/* split the copy and save the tokens in argv*/
token = strtok(prompt_copy, delimiter);
for (i = 0; token != NULL; i++){
argv[i] = malloc(sizeof(char) * strlen(token));
strcpy(argv[i], token);
token = strtok(NULL, delimiter);
}
argv[i] = NULL;

/*execute the carguments*/
exec_command(argv);
}
free(prompt_copy);
free(prompt);

return (0);
}
