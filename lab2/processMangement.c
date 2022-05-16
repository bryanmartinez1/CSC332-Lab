#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    pid_t pid, c_pid;
    int x = 6;

    c_pid = fork();
    if (c_pid == 0) {
        printf("in child process. CHild pid: %d\n", getpid());
        x = x + 2;
        printf("in child value x: %d\n", x);
    }
    else if (c_pid == -1) {
        printf("fork failed. \n");
    }
    else {
        printf("in parent process. Parent process: %d\n", getpid);
        x = x - 2;
        printf("in parent value of x: %d\n", x);
    }
}