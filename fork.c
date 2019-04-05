#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

void doSomething(char a) {
    int i;
    char buf[100];

    i = (int) a - '0';
    sprintf (buf, "The square of %c is %d\n", a, i*i);
    write (1, buf, strlen(buf));
}

int main (int argc, char **argv) {
    int i;
    pid_t pid;

    for (i = 1; i < argc;) {
        doSomething(*argv[i++]);
        pid = fork();
        kill(pid, SIGTERM);
        sleep(0.5);
    }
    return 0;
}
