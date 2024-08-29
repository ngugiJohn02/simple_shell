#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
char *argv[] = {"ls", "-l", "/tmp", NULL}; /* command and arguments */
char *pathname = "/bin/ls"; /* path to the executable */

for (int i = 0; i < 5; i++) {
pid_t pid = fork();

if (pid == 0) { /* child process */
printf("Child %d: executing ls -l /tmp\n", i);
execve(pathname, argv, NULL);
perror("execve");
return 1;
} else { /* parent process */
printf("Parent: created child %d\n", i);
wait(NULL); /* wait for child to exit */
}
}

return 0;
}
