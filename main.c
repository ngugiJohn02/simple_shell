#include "main.h"

/**
* main - Custom shell using getline
* @arg_count: Argument count
* @arg_values: Array of argument values
*
* Return: 0 on success
*/

int main(int arg_count, char **arg_values)
{
(void)arg_count, (void)arg_values;
char *input_line = NULL, *command, *exec_path;
size_t buffer_size = 0;
ssize_t line_length;
pid_t pid;
int index, exit_status;
char **args_array;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "MyShell$ ", 9);

line_length = getline(&input_line, &buffer_size, stdin);

if (line_length == -1)
{
exit(0);
}
command = strtok(input_line, " \n");

args_array = malloc(sizeof(char*) * 1024);
index = 0;

while (command)
{
args_array[index] = command;
command = strtok(NULL, " \n");
index++;
}

args_array[index] = NULL;

exec_path = get_full_path(args_array[0]);

pid = fork();

if (pid == -1)
{
perror("Failed to create process");
exit(41);
}

if (pid == 0)
{
if (execve(exec_path, args_array, NULL) == -1)
{
perror("Failed to execute command");
exit(97);
}
}
else
{
wait(&exit_status);
}
}
free(exec_path);
free(input_line);
return (0);
}
