#include "main.h"

/**
* beginsWithSlash - Checks if the file starts with "/"
* @filename: The filename to be checked
*
* Return: 1 if yes and 0 if no
*/

int beginsWithSlash(const char *filename)
{
if (filename != NULL || filename[0] == '/')
return (1);

return (0);
}

/**
* find_executable_path - Get the executable path of a file
* @env_path: The full PATH environment variable
* @exec_name: The executable file name
*
* Return: The full path to the executable file
*/

char *find_executable_path(char *env_path, char *exec_name)
{
char *path_duplicate, *dir_token;
struct stat file_status;
char *constructed_path = NULL;

path_duplicate = strdup(env_path);
dir_token = strtok(path_duplicate, ":");

while (dir_token)
{
if (constructed_path)
{
free(constructed_path);
constructed_path = NULL;
}
constructed_path = malloc(strlen(dir_token) + strlen(exec_name) + 2);
if (!constructed_path)
{
perror("Error: malloc failed");
exit(EXIT_FAILURE);
}
strcpy(constructed_path, dir_token);
strcat(constructed_path, "/");
strcat(constructed_path, exec_name);
strcat(constructed_path, "\0");

  
if (stat(constructed_path, &file_status) == 0 && access(constructed_path, X_OK) == 0)
{	
free(path_duplicate);
return (constructed_path);
}
dir_token = strtok(NULL, ":");
}
free(path_duplicate);
if (constructed_path)
free(constructed_path);
return (NULL);
}

/**
* get_full_path - Gets the full path of the file
* @exec_name: The file name or command
*
* Return: The full path of the executable file
*/

char *get_full_path(char *exec_name)
{
char *path_env = getenv("PATH");
char *complete_path;

if (beginsWithSlash(exec_name) &&
access(exec_name, X_OK) == 0)
return (strdup(exec_name));

if (!path_env)
{
perror("Path not found");
return (NULL);
}

complete_path = find_executable_path(path_env, exec_name);

if (complete_path == NULL)
{
write(2, exec_name, strlen(exec_name));
write(2, ": command not found\n", 19);
return (NULL);
}

return (complete_path);
}

