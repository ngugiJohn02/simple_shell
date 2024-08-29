#include "main.h"

/**
* parse_input - function that tokenizes the input string
* into individual arguments
* @line: input string to be tokenized
* @argv: array of string with each holding a token
* @argc: pointer to an integer storing no of args passed
* to execute the inputted command
* @history: array to store the command history
* @history_count: pointer to an integer storing the count of commands in history
*/
void parse_input(char *line, char **argv, int *argc, char ***history, int *history_count)
{
char *token;
char *delim = " \n";
*argc = 0;
token = strtok(line, delim);
while (token)
{
argv[*argc] = token;
(*argc)++;
token = strtok(NULL, delim);
}

argv[*argc] = NULL;

// Store the command in history
(*history_count)++;
*history = realloc(*history, (*history_count) * sizeof(char *));
(*history)[*history_count - 1] = malloc(strlen(line) + 1);
strcpy((*history)[*history_count - 1], line);
}

/**
* execute_command - function that creates a child process
* that executes the command inputted
* @argv: Array of strings where the first element is the
* command to be executed while the following elements
* are arguments
* @last_exit_status: pointer to an integer storing the exit status of the last command
*/
void execute_command(char **argv, int *last_exit_status)
{
pid_t child_pid;
int status;
struct stat st;

child_pid = fork();
if (child_pid == 0)
{
if (stat(argv[0], &st) == 0)
{
if (execve(argv[0], argv, environ) == -1)
{
perror("execve failed:(\n");
exit(1);
}
}
else
{
perror("Command NOT FOUND:(\n");
exit(127);
}
}
else if (child_pid > 0)
{
wait(&status);
*last_exit_status = WEXITSTATUS(status);
}
else
{
perror("fork failed");
exit(1);
}
}

/**
* print_history - function to print the command history
* @history: array of strings storing the command history
* @history_count: integer storing the count of commands in history
*/
void print_history(char **history, int history_count)
{
int i;
for (i = 0; i < history_count; i++)
{
printf("%d: %s\n", i + 1, history[i]);
}
}

int main()
{
char line[1024];
char *argv[64];
int argc;
char **history = NULL;
int history_count = 0;
int last_exit_status;

while (1)
{
printf("shell> ");
fgets(line, 1024, stdin);
line[strlen(line) - 1] = '\0'; // Remove the newline character

parse_input(line, argv, &argc, &history, &history_count);
execute_command(argv, &last_exit_status);

if (strcmp(argv[0], "history") == 0)
{
print_history(history, history_count);
}
}

return 0;
}
