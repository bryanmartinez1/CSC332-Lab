#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {
    int child_pid_1 = fork(), child_pid_2;
    char* process1 = "process1.exe";
    char* process2 = "process2.exe";

    if(child_pid_1 < 0 ) {
        printf("Error in Fork\n");
    }
// Child Process
    else if (child_pid_1 == 0) {
        char *const argv[] = {process1, NULL};
        execv(argv[0], argv);
        //Error in execv function
        printf("execv error for Child 1\n");
    }
//Parent Process
    else {
        wait(NULL);
        child_pid_2 = fork();
        if(child_pid_2 < 0 ) {
            printf("Error in Fork\n");
            return 0;
        }
    // Child Process
        else if (child_pid_2 == 0) {
            wait(NULL);
            char *const argv[] = {process2, NULL};
            execv(argv[0], argv);
            printf("execv error for Child 2\n");
            return 0;
        }
    }
    
    return 0;
}