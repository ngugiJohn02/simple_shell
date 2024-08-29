#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
char *path = getenv("PATH");
char *token;
char pathbuf[1024];

if (argc < 2) {
fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
return 1;
}

token = strtok(path, ":");
while (token != NULL) {
sprintf(pathbuf, "%s/%s", token, argv[1]);
if (access(pathbuf, X_OK) == 0) {
printf("%s\n", pathbuf);
return 0;
}
token = strtok(NULL, ":");
}

fprintf(stderr, "%s: not found\n", argv[1]);
return 1;
}
