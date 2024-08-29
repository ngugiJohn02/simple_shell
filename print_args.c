#include <stdio.h>

int main() {
extern char **environ;
char **arg = environ - 1;

while (*arg != NULL) {
printf("%s\n", *arg);
arg++;
}

return 0;
}
