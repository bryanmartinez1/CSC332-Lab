#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    //Gets child 2
    int c_pid_1 = fork();
    pid_t wpid;
    if(c_pid_1 == -1) {
        printf("Fork failed\n");
    }
    else if (c_pid_1 == 0) {
        printf("I am child one, my pid is: %i\n", getpid());
        while(wait(NULL) > 0);
    }
    else if (c_pid_1 > 0) {
        int c_pid_2 = fork();
        if(c_pid_2 == -1) {
            printf("Fork failed\n");
        }
        else if (c_pid_2 == 0) {
            printf("I am child two, my pid is: %i\n", getpid());
        }
        while(wait(NULL) > 0);
    }
    printf("\n");
    return 0;
}