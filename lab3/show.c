#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {
    int child_pid = fork();

    if(child_pid < 0 ) {
        printf("Error in Fork\n");
    }
// Child Process
    else if (child_pid == 0) {
        printf("Child Process: %i\n", getpid());
        char *argv[] = {"ls", "-a", "-l", NULL};
        execvp(argv[0], argv);
    }
//Parent Process
    else {
        wait(NULL);
    }
    
    return 0;
}