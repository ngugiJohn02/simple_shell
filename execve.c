#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

char *argv[] = {"ls", "-l", NULL}; /* command and arguments */
char *pathname = "/bin/ls"; /* path to the executable */

printf("Before execve\n");

/* Execute the new program */
execve(pathname, argv, NULL);

/* execve returns, it means an error occurred */
perror("execve");
return 1;
}
