#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {
    int status;
    int child_pid = fork();

    if(child_pid < 0) {
        printf("Error in fork\n");
    }
//Child
    else if (child_pid == 0) {
    // Prints Child ID
        printf("Child Pid: %i\n", getpid());

    // Time Command
        execl("/bin/date", "date",NULL);
    }
//Parent
    else {
    // Waits for child
        wait(NULL);
    }

    return 0;
}